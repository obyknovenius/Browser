//
//  TreeConstruction.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#include "../DOM/Comment.h"
#include "Token.h"
#include "TreeConstruction.h"

namespace HTML {

void insert_comment(const Comment* comment, DOM::Node* target)
{
    const auto& data = comment->data();
    auto* node = new DOM::Comment { data };
    target->children().push_back(node);
}

bool TreeConstruction::dispatch(Token* token)
{
    process_using_rules_for_current_insertion_mode(token);
    
    bool eof { false };
    
    if (auto* doctype = token->as<HTML::Doctype*>())
    {
        std::cout << *doctype;
    }
    
    if (auto* start_tag = token->as<HTML::StartTag*>())
    {
        std::cout << *start_tag;
    }
    
    if (auto* end_tag = token->as<HTML::EndTag*>())
    {
        std::cout << *end_tag;
    }
    
    if (auto* comment = token->as<HTML::Comment*>())
    {
        std::cout << *comment;
    }
    
    if (auto* character = token->as<HTML::Character*>())
    {
        std::cout << *character;
    }
    
    if (auto* end_of_file = token->as<HTML::EndOfFile*>())
    {
        std::cout << *end_of_file;
        eof = true;
    }
    
    delete token;
    
    return eof;
}

void TreeConstruction::process_using_rules_for_current_insertion_mode(Token* token)
{
    switch (m_insertion_mode) {
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
    if (auto* comment = token->as<HTML::Comment*>())
    {
        insert_comment(comment, &m_document);
        return;
    }
    switch_to(InsertionMode::BeforeHtml);
    reprocess(token);
}

void TreeConstruction::apply_rules_for_before_html_insertion_mode(Token* token)
{
    
}

}
