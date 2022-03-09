//
//  TreeConstruction.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#include "../DOM/Node.h"
#include "../DOM/DocumentType.h"
#include "../DOM/Comment.h"
#include "Token.h"
#include "TreeConstruction.h"

namespace HTML {

void insert_comment(const Comment* comment, DOM::Node* target)
{
    const auto& data = comment->data();
    auto* node = new DOM::Comment { data };
    target->children().append(node);
}

void TreeConstruction::dispatch(Token* token)
{
    process_using_rules_for_current_insertion_mode(token);
    
    if (auto* doctype = token->as<Doctype*>())
    {
        std::cout << *doctype;
    }
    
    if (auto* start_tag = token->as<StartTag*>())
    {
        std::cout << *start_tag;
    }
    
    if (auto* end_tag = token->as<EndTag*>())
    {
        std::cout << *end_tag;
    }
    
    if (auto* comment = token->as<Comment*>())
    {
        std::cout << *comment;
    }
    
    if (auto* character = token->as<Character*>())
    {
        std::cout << *character;
    }
}

void TreeConstruction::process_using_rules_for_current_insertion_mode(Token* token)
{
    switch (m_insertion_mode)
    {
        case InsertionMode::Initial:
            apply_rules_for_initial_insertion_mode(token);
            break;
        case InsertionMode::BeforeHtml:
            apply_rules_for_before_html_insertion_mode(token);
            break;
    }
}

void TreeConstruction::apply_rules_for_initial_insertion_mode(Token* token)
{
    if (auto* comment = token->as<Comment*>())
    {
        insert_comment(comment, &m_document);
        return;
    }
    
    if (auto* doctype = token->as<Doctype*>())
    {
        auto* document_type = new DOM::DocumentType { *doctype->name() };
        append(document_type, &m_document);
        switch_to(InsertionMode::BeforeHtml);
        return;
    }
    
    switch_to(InsertionMode::BeforeHtml);
    reprocess(token);
}

void TreeConstruction::apply_rules_for_before_html_insertion_mode(Token* token)
{
    if (auto* character = token->as<Character*>(); character && character->is_one_of({'\t', '\n', '\f', ' '}))
    {
        return;
    }
}

}
