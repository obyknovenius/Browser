//
//  TreeConstructor.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#include "../Infra/Namespace.h"
#include "../DOM/Node.h"
#include "../DOM/Element.h"
#include "../DOM/DocumentType.h"
#include "../DOM/Comment.h"
#include "../DOM/Text.h"
#include "XMLCompatability.h"
#include "Token.h"
#include "TreeConstructor.h"

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

void insert_at(InsertionLocation location, Node* node)
{
    insert(node, location.inside, location.before);
}

InsertionLocation TreeConstructor::appropriate_place_for_inserting_node()
{
    Node* target { current_node() };
    InsertionLocation adjusted_insertion_location { target };
    return adjusted_insertion_location;
}

Element* TreeConstructor::create_element_for(const Token& token, const std::string& namespace_, Node* intended_parent)
{
    auto* document { intended_parent->node_document() };
    auto& local_name { token.tag_name() };
    auto* element { create_element(document, local_name, namespace_) };
    return element;
}

Element* TreeConstructor::insert_foreign_element_for(const Token& token, const std::string& namespace_)
{
    auto adjusted_insertion_location { appropriate_place_for_inserting_node() };
    auto* element { create_element_for(token, namespace_, adjusted_insertion_location.inside) };
    insert_at(adjusted_insertion_location, element);
    m_stack_of_open_elements.push(element);
    return element;
}

Element* TreeConstructor::insert_html_element_for(const Token& token)
{
    return insert_foreign_element_for(token, Namespace::HTML);
}

void TreeConstructor::insert_character(const Token& token)
{
    auto data { token.data() };
    auto adjusted_insertion_location { appropriate_place_for_inserting_node() };
    if (adjusted_insertion_location.inside->is<Document>())
    {
        return;
    }
    
    if (auto* node { immediately_before(adjusted_insertion_location)->is<Text>() })
    {
        node->data() += data;
    }
    else
    {
        node = new Text { data };
        insert_at(adjusted_insertion_location, node);
    }
}

void TreeConstructor::insert_comment(const Token& token, std::optional<InsertionLocation> position)
{
    const auto& data { token.data() };
    auto adjusted_insertion_location { position ? *position : appropriate_place_for_inserting_node() };
    auto* node { new Comment { data } };
    insert_at(adjusted_insertion_location, node);
}

bool TreeConstructor::construct_tree()
{
    while (!m_tokens.empty())
    {
        const Token& next_token = m_tokens.front();
        dispatch(next_token);
        m_tokens.pop();
        
        std::cout << next_token;
        
        if (next_token.is_end_of_file())
        {
            return true;
        }
    }
    return false;
}

void TreeConstructor::dispatch(const Token& token)
{
    process_using_rules_for(m_insertion_mode, token);
}

void TreeConstructor::process_using_rules_for(InsertionMode insertion_mode, const Token& token)
{
    switch (insertion_mode)
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
        case InsertionMode::AfterBody:
        {
            apply_rules_for_after_body_insertion_mode(token);
            break;
        }
        case InsertionMode::AfterAfterBody:
        {
            apply_rules_for_after_after_body_insertion_mode(token);
            break;
        }
    }
}

void TreeConstructor::apply_rules_for_initial_insertion_mode(const Token& token)
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

void TreeConstructor::apply_rules_for_before_html_insertion_mode(const Token& token)
{
    if (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    {
        return;
    }
    
    if (token.is_start_tag() && token.tag_name_is("html"))
    {
        auto* element { create_element_for(token, Namespace::HTML, &m_document) };
        append(element, &m_document);
        m_stack_of_open_elements.push(element);
        switch_to(InsertionMode::BeforeHead);
        return;
    }
}

void TreeConstructor::apply_rules_for_before_head_insertion_mode(const Token& token)
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
    
    if (token.is_start_tag() && token.tag_name_is("head"))
    {
        auto* element { insert_html_element_for(token) };
        m_head_element_pointer = element;
        switch_to(InsertionMode::InHead);
        return;
    }
}

void TreeConstructor::apply_rules_for_in_head_insertion_mode(const Token& token)
{
    if (token.is_end_tag() && token.tag_name_is("head"))
    {
        m_stack_of_open_elements.pop();
        switch_to(InsertionMode::AfterHead);
        return;
    }
}

void TreeConstructor::apply_rules_for_after_head_insertion_mode(const Token& token)
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
    
    if (token.is_start_tag() && token.tag_name_is("body"))
    {
        insert_html_element_for(token);
        m_frameset_ok_flag = FramesetOkFlag::NotOk;
        switch_to(InsertionMode::InBody);
        return;
    }
}

void TreeConstructor::apply_rules_for_in_body_insertion_mode(const Token& token)
{
    if (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    {
        insert_character(token);
        return;
    }
    
    if (token.is_character())
    {
        insert_character(token);
        m_frameset_ok_flag = FramesetOkFlag::NotOk;
        return;
    }
    
    if (token.is_end_tag() && token.tag_name_is("body"))
    {
        switch_to(InsertionMode::AfterBody);
        return;
    }
    
    if (token.is_start_tag() && token.tag_name_is_one_of({"h1", "h2", "h3", "h4", "h5", "h6"}))
    {
        insert_html_element_for(token);
        return;
    }
    
    if (token.is_end_tag() && token.tag_name_is_one_of({"h1", "h2", "h3", "h4", "h5", "h6"}))
    {
        m_stack_of_open_elements.pop_until([](Element* element)
        {
            return is_html_element(*element) && element->tag_name_is_one_of({"h1", "h2", "h3", "h4", "h5", "h6"});
        });
        return;
    }
}

void TreeConstructor::apply_rules_for_after_body_insertion_mode(const Token& token)
{
    if (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    {
        process_using_rules_for(InsertionMode::InBody, token);
        return;
    }
    
    if (token.is_comment())
    {
        insert_comment(token, InsertionLocation { m_stack_of_open_elements.topmost()} );
        return;
    }
    
    if (token.is_end_tag() && token.tag_name_is("body"))
    {
        switch_to(InsertionMode::AfterAfterBody);
    }
}

void TreeConstructor::apply_rules_for_after_after_body_insertion_mode(const Token& token)
{
    if (token.is_comment())
    {
        insert_comment(token, InsertionLocation { &m_document} );
        return;
    }
    
    if (token.is_doctype()
    || (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    || (token.is_start_tag() && token.tag_name_is("html")))
    {
        process_using_rules_for(InsertionMode::InBody, token);
        return;
    }
    
    if (token.is_end_of_file())
    {
        stop_parsing();
    }
}

void TreeConstructor::stop_parsing()
{
    m_stack_of_open_elements.pop_all();
}

}
