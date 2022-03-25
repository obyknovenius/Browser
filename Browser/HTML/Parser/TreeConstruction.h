//
//  TreeConstruction.h
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#pragma once

#include "Document.h"
#include "Token.h"
#include "StackOfOpenElements.h"
#include "../../DOM/Element.h"
#include <queue>
#include <optional>

using namespace DOM;

namespace HTML {

struct InsertionLocation
{
    Node* inside { nullptr };
    Node* before { nullptr };
};

class TreeConstruction
{
public:
    TreeConstruction(Document& document, std::queue<Token>& tokens) : m_document { document }, m_tokens { tokens } {}
    
    bool construct_tree();
    
private:
    Document& m_document;
    
    std::queue<Token>& m_tokens;
    
    enum class InsertionMode
    {
        Initial,
        BeforeHtml,
        BeforeHead,
        InHead,
        AfterHead,
        InBody,
        AfterBody,
        AfterAfterBody
    };
    
    InsertionMode m_insertion_mode { InsertionMode::Initial };
    
    StackOfOpenElements m_stack_of_open_elements {};
    
    Element* m_head_element_pointer { nullptr };
    
    enum class FramesetOkFlag
    {
        Ok,
        NotOk,
    };
    
    FramesetOkFlag m_frameset_ok_flag { FramesetOkFlag::Ok };
    
    void dispatch(const Token& token);
    
    void switch_to(InsertionMode insertion_mode) { m_insertion_mode = insertion_mode; }
        
    Node* current_node() { return m_stack_of_open_elements.bottommost(); }
        
    void process_using_the_rules_for(InsertionMode insertion_mode, const Token& token);
    void reprocess(const Token& token)
    {
        process_using_the_rules_for(m_insertion_mode, token);
    }
    
    void apply_rules_for_initial_insertion_mode(const Token& token);
    void apply_rules_for_before_html_insertion_mode(const Token& token);
    void apply_rules_for_before_head_insertion_mode(const Token& token);
    void apply_rules_for_in_head_insertion_mode(const Token& token);
    void apply_rules_for_after_head_insertion_mode(const Token& token);
    void apply_rules_for_in_body_insertion_mode(const Token& token);
    void apply_rules_for_after_body_insertion_mode(const Token& token);
    void apply_rules_for_after_after_body_insertion_mode(const Token& token);
    
    InsertionLocation appropriate_place_for_inserting_node();
    
    Element* create_element_for(const Token& token, const std::string& namespace_, Node* intended_parent);
    
    Element* insert_foreign_element_for(const Token& token, const std::string& namespace_);
    Element* insert_html_element_for(const Token& token);
    
    void insert_character(const Token& token);
    void insert_comment(const Token& token, std::optional<InsertionLocation> position = std::nullopt);
    
    void stop_parsing();
};

}
