//
//  TreeConstruction.h
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#pragma once

#include "Document.h"
#include "Token.h"
#include <stack>
#include <optional>

using namespace DOM;

namespace HTML {

class TreeConstruction
{
    enum class InsertionMode
    {
        Initial,
        BeforeHtml,
        BeforeHead,
    };
    
    struct InsertionLocation
    {
        Node* target { nullptr };
        Node* child { nullptr };
    };
    
    Document& m_document;
    
    InsertionMode m_insertion_mode { InsertionMode::Initial };
    
    std::stack<Node*> m_stack_of_open_elements;
    
    Node* current_node() { return m_stack_of_open_elements.top(); }
    
    void switch_to(InsertionMode insertion_mode)
    {
        m_insertion_mode = insertion_mode;
    }
    
    void process_using_rules_for_current_insertion_mode(Token*);
    void reprocess(Token* token)
    {
        process_using_rules_for_current_insertion_mode(token);
    }
    
    void apply_rules_for_initial_insertion_mode(Token*);
    void apply_rules_for_before_html_insertion_mode(Token*);
    void apply_rules_for_before_head_insertion_mode(Token*);
    
    
    
    InsertionLocation appropriate_place_for_inserting_node();
    
    void insert_comment(const Comment* comment, std::optional<InsertionLocation> position = std::nullopt);
    
public:
    TreeConstruction(Document& document) : m_document { document } {}
    
    void dispatch(Token*);
};

}
