//
//  TreeConstruction.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#include "../../Infra/Namespace.h"
#include "../../DOM/Node.h"
#include "../../DOM/Element.h"
#include "../../DOM/DocumentType.h"
#include "../../DOM/Comment.h"
#include "../../DOM/Text.h"
#include "Token.h"
#include "TreeConstruction.h"

using namespace Infra;
using namespace DOM;

namespace HTML {

Node* immediately_before(InsertionLocation location)
{
    if (location.before != nullptr)
    {
        return location.before->previous_sibling();
    }
    return location.inside->last_child();
}

void insert_at(Node* node, InsertionLocation location)
{
    insert(node, location.inside, location.before);
}

InsertionLocation TreeConstruction::appropriate_place_for_inserting_node()
{
    Node* target { current_node() };
    InsertionLocation adjusted_insertion_location { target };
    return adjusted_insertion_location;
}

Element* TreeConstruction::create_element_for(const Token& token, std::string_view namespace_, Node* intended_parent)
{
    auto* document { intended_parent->node_document() };
    const std::string_view local_name { token.tag_name() };
    auto* element { create_element(document, local_name, namespace_) };
    return element;
}

Element* TreeConstruction::insert_foreign_element_for(const Token& token, std::string_view namespace_)
{
    auto adjusted_insertion_location { appropriate_place_for_inserting_node() };
    auto* element { create_element_for(token, namespace_, adjusted_insertion_location.inside) };
    insert_at(element, adjusted_insertion_location);
    stack_of_open_elements().push(element);
    return element;
}

Element* TreeConstruction::insert_html_element_for(const Token& token)
{
    return insert_foreign_element_for(token, Namespace::HTML);
}

void TreeConstruction::insert_character(const Token& token)
{
    auto data { token.data() };
    auto adjusted_insertion_location { appropriate_place_for_inserting_node() };
    if (adjusted_insertion_location.inside->is<Document>())
    {
        return;
    }
    
    if (auto* node { immediately_before(adjusted_insertion_location)->is<Text>() }; node)
    {
        node->data() += token.data();
    }
    else
    {
        node = new Text { data };
        insert_at(node, adjusted_insertion_location);
    }
}

void TreeConstruction::insert_comment(const Token& token, std::optional<InsertionLocation> position)
{
    const auto& data { token.data() };
    auto adjusted_insertion_location { position ? *position : appropriate_place_for_inserting_node() };
    auto* node { new Comment { data } };
    insert_at(node, adjusted_insertion_location);
}

void TreeConstruction::dispatch(const Token& token)
{
    process_using_rules_for_current_insertion_mode(token);
}

void TreeConstruction::process_using_rules_for_current_insertion_mode(const Token& token)
{
    switch (m_insertion_mode)
    {
        case InsertionMode::Initial:
        {
            apply_rules_for_initial_insertion_mode(token);
            break;
        }
        case InsertionMode::BeforeHtml:
        {
            apply_rules_for_before_html_insertion_mode(token);
            break;
        }
        case InsertionMode::BeforeHead:
        {
            apply_rules_for_before_head_insertion_mode(token);
            break;
        }
        case InsertionMode::InHead:
        {
            apply_rules_for_in_head_insertion_mode(token);
            break;
        }
        case InsertionMode::AfterHead:
        {
            apply_rules_for_after_head_insertion_mode(token);
            break;
        }
        case InsertionMode::InBody:
        {
            apply_rules_for_in_body_insertion_mode(token);
            break;
        }
    }
}

void TreeConstruction::apply_rules_for_initial_insertion_mode(const Token& token)
{
    if (token.is_comment())
    {
        insert_comment(token, InsertionLocation { &m_document });
        return;
    }
    
    if (token.is_doctype())
    {
        auto* document_type = new DocumentType { *token.name() };
        append(document_type, &m_document);
        switch_to(InsertionMode::BeforeHtml);
        return;
    }
    
    switch_to(InsertionMode::BeforeHtml);
    reprocess(token);
}

void TreeConstruction::apply_rules_for_before_html_insertion_mode(const Token& token)
{
    if (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    {
        return;
    }
    
    if (token.is_start_tag() && token.tag_name() == "html")
    {
        auto* element { create_element_for(token, Namespace::HTML, &m_document) };
        append(element, &m_document);
        stack_of_open_elements().push(element);
        switch_to(InsertionMode::BeforeHead);
        return;
    }
}

void TreeConstruction::apply_rules_for_before_head_insertion_mode(const Token& token)
{
    if (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    {
        return;
    }
    
    if (token.is_comment())
    {
        insert_comment(token);
        return;
    }
    
    if (token.is_start_tag() && token.tag_name() == "head")
    {
        auto* element { insert_html_element_for(token) };
        m_head_element_pointer = element;
        switch_to(InsertionMode::InHead);
        return;
    }
}

void TreeConstruction::apply_rules_for_in_head_insertion_mode(const Token& token)
{
    if (token.is_end_tag() && token.tag_name() == "head")
    {
        stack_of_open_elements().pop();
        switch_to(InsertionMode::AfterHead);
        return;
    }
}

void TreeConstruction::apply_rules_for_after_head_insertion_mode(const Token& token)
{
    if (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    {
        insert_character(token);
        return;
    }
    
    if (token.is_comment())
    {
        insert_comment(token);
        return;
    }
    
    if (token.is_start_tag() && token.tag_name() == "body")
    {
        insert_html_element_for(token);
        set_frameset_ok_flag(FramesetOkFlag::NotOk);
        switch_to(InsertionMode::InBody);
        return;
    }
}

void TreeConstruction::apply_rules_for_in_body_insertion_mode(const Token& token)
{
    if (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    {
        insert_character(token);
        return;
    }
    
    if (token.is_character())
    {
        insert_character(token);
        set_frameset_ok_flag(FramesetOkFlag::NotOk);
        return;
    }
    
    if (token.is_start_tag() && token.tag_name_is_one_of({"h1", "h2", "h3", "h4", "h5", "h6"}))
    {
        insert_html_element_for(token);
        return;
    }
}

}
