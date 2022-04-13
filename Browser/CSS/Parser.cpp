//
//  Parser.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#include "Parser.h"

namespace CSS {

ComponentValue Parser::consume_component_value()
{
    const auto& token { m_input.consume_next_token() };
    
    if (token.is_left_curly_bracket())
    {
        return consume_simple_block();
    }
    return token;
}

ComponentValue Parser::consume_simple_block()
{
    ComponentValue simple_block { ComponentValue::Type::SimpleBlock, m_input.current_token() };
    
    for(;;)
    {
        const auto& token { m_input.consume_next_token() };
        
        if (token.is_ending(simple_block.m_token))
        {
            return simple_block;
        }
        else
        {
            m_input.reconsume();
            simple_block.m_value.push_back(consume_component_value());
        }
    }
}

QualifiedRule Parser::consume_qualified_rule()
{
    QualifiedRule qualified_rule {};
    
    for(;;)
    {
        const auto& token { m_input.consume_next_token() };
        
        if (token.is_left_curly_bracket())
        {
            qualified_rule.m_block = consume_simple_block();
            return qualified_rule;
        }
        else
        {
            m_input.reconsume();
            qualified_rule.m_prelude.push_back(consume_component_value());
        }
    }
}

std::list<QualifiedRule> Parser::consume_list_of_rules()
{
    std::list<QualifiedRule> list_of_rules {};
    
    for(;;)
    {
        const auto& token { m_input.consume_next_token() };
        
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
            m_input.reconsume();
            list_of_rules.push_back(consume_qualified_rule());
        }
    }
}

QualifiedRule Parser::parse_rule()
{
    while (m_input.next_token().is_whitespace())
    {
        m_input.consume_next_token();
    }
    
    auto rule { consume_qualified_rule() };
    
    while (m_input.next_token().is_whitespace())
    {
        m_input.consume_next_token();
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
