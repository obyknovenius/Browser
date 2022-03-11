//
//  TreeConstruction.h
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#pragma once

#include "Document.h"
#include "Token.h"
#include "../DOM/Element.h"
#include <stack>
#include <optional>

using namespace DOM;

namespace HTML {

class TreeConstruction
{
public:
    TreeConstruction(Document& document) : m_document { document } {}
    
    void dispatch(const Token&);
    
private:
    enum class InsertionMode
    {
        Initial,
        BeforeHtml,
        BeforeHead,
        InHead,
    };
    
    Document& m_document;
    
    InsertionMode m_insertion_mode { InsertionMode::Initial };
    
    std::stack<Node*> m_stack_of_open_elements {};
    
    Element* m_head_element_pointer { nullptr };

    Node* current_node() { return m_stack_of_open_elements.top(); }
    
    void switch_to(InsertionMode insertion_mode)
    {
        m_insertion_mode = insertion_mode;
    }
    
    void process_using_rules_for_current_insertion_mode(const Token& token);
    void reprocess(const Token& token)
    {
        process_using_rules_for_current_insertion_mode(token);
    }
    
    void apply_rules_for_initial_insertion_mode(const Token& token);
    void apply_rules_for_before_html_insertion_mode(const Token& token);
    void apply_rules_for_before_head_insertion_mode(const Token& token);
    
    struct InsertionLocation
    {
        Node* target { nullptr };
        Node* child { nullptr };
    };
    
    InsertionLocation appropriate_place_for_inserting_node();
    
    Element* create_element_for_token(const Token& token, std::string_view namespace_, Node* intended_parent);
    
    Element* insert_foreign_element(const Token& token, std::string_view namespace_);
    
    Element* insert_html_element(const Token& token);
    
    void insert_comment(const Token& comment, std::optional<InsertionLocation> position = std::nullopt);
};

}
