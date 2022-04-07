//
//  Parser.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#include "Parser.h"

namespace CSS {

const Token& Parser::next_input_token()
{
    if (m_tokens.empty())
    {
        return m_eof_token;
    }
    return m_tokens.front();
}

const Token& Parser::consume_next_input_token()
{
    if (m_reconsume)
    {
        m_reconsume = false;
        return m_current_input_token;
    }
    
    m_current_input_token = next_input_token();
    if (!m_tokens.empty())
    {
        m_tokens.pop();
    }
    return m_current_input_token;
}

ComponentValue Parser::consume_component_value()
{
    const Token& token { consume_next_input_token() };
    
    if (token.is_left_curly_bracket())
    {
        return consume_simple_block();
    }
    return m_current_input_token;
}

ComponentValue Parser::consume_simple_block()
{
    ComponentValue simple_block { ComponentValue::Type::SimpleBlock, m_current_input_token };
    
    for(;;)
    {
        const Token& token { consume_next_input_token() };
        
        if (token.is_ending(simple_block.m_token))
        {
            return simple_block;
        }
        else
        {
            reconsume_current_input_token();
            simple_block.m_value.push_back(consume_component_value());
        }
    }
}

QualifiedRule Parser::consume_qualified_rule()
{
    QualifiedRule qualified_rule {};
    
    for(;;)
    {
        const Token& token { consume_next_input_token() };
        
        if (token.is_left_curly_bracket())
        {
            qualified_rule.m_block = consume_simple_block();
            return qualified_rule;
        }
        else
        {
            reconsume_current_input_token();
            qualified_rule.m_prelude.push_back(consume_component_value());
        }
    }
}

std::list<QualifiedRule> Parser::consume_list_of_rules()
{
    std::list<QualifiedRule> list_of_rules {};
    
    for(;;)
    {
        const Token& token { consume_next_input_token() };
        
        if (token.is_whitespace())
        {
            // Do nothing.
        }
        else if (token.is_eof())
        {
            return list_of_rules;
        }
        else
        {
            reconsume_current_input_token();
            
            list_of_rules.push_back(consume_qualified_rule());
        }
    }
}

QualifiedRule Parser::parse_rule()
{
    while (next_input_token().is_whitespace())
    {
        consume_next_input_token();
    }
    
    auto rule { consume_qualified_rule() };
    
    while (next_input_token().is_whitespace())
    {
        consume_next_input_token();
    }
    
    return rule;
}

StyleSheet Parser::parse_stylesheet()
{
    StyleSheet style_sheet {};
    style_sheet.m_value = consume_list_of_rules();
    return style_sheet;
}

}
