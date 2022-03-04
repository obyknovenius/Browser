//
//  TreeConstruction.h
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#pragma once

#include "Document.h"
#include "Token.h"

namespace HTML {

class TreeConstruction
{
    enum class InsertionMode
    {
        Initial,
        BeforeHtml,
    };
    
    DOM::Document& m_document;
    
    InsertionMode m_insertion_mode { InsertionMode::Initial };
    
    DOM::Node* m_current_node {};
    
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
    
public:
    TreeConstruction(DOM::Document& document) : m_document { document } {}
    
    void dispatch(Token*);
};

}
