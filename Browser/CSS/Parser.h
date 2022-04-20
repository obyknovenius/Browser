//
//  Parser.h
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#pragma once

#include "TokenStream.h"
#include "Token.h"
#include "SimpleBlock.h"
#include "ComponentValue.h"
#include "QualifiedRule.h"
#include "StyleSheet.h"
#include "Selectors/SimpleSelector.h"
#include <list>

namespace CSS::Parser {

template<typename T>
ComponentValue consume_component_value(TokenStream<T>& input);

template<typename T>
SimpleBlock* consume_simple_block(TokenStream<T>& input)
{
    auto* simple_block { new SimpleBlock { input.current_token() } };
    
    for (;;)
    {
        const auto& token { input.consume_next_token() };
        
        if (token.is_ending(simple_block->token()))
        {
            return simple_block;
        }
        else
        {
            input.reconsume();
            simple_block->m_value.push_back(consume_component_value(input));
        }
    }
}

template<typename T>
ComponentValue consume_component_value(TokenStream<T>& input)
{
    const auto& token { input.consume_next_token() };
    
    if (token.is_left_curly_bracket())
    {
        return consume_simple_block(input);
    }
    return token;
}

template<typename T>
QualifiedRule* consume_qualified_rule(TokenStream<T>& input)
{
    auto* qualified_rule { new QualifiedRule };
    
    for (;;)
    {
        const auto& token { input.consume_next_token() };
        
        if (token.is_left_curly_bracket())
        {
            qualified_rule->m_block = consume_simple_block(input);
            return qualified_rule;
        }
        else
        {
            input.reconsume();
            qualified_rule->m_prelude.push_back(consume_component_value(input));
        }
    }
}

template<typename T>
std::list<QualifiedRule*> consume_list_of_rules(TokenStream<T>& input)
{
    std::list<QualifiedRule*> list_of_rules {};
    
    for (;;)
    {
        const auto& token { input.consume_next_token() };
        
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
            input.reconsume();
            list_of_rules.push_back(consume_qualified_rule(input));
        }
    }
}

template<typename T>
QualifiedRule* parse_rule(TokenStream<T>& input)
{
    while (input.next_token().is_whitespace())
    {
        input.consume_next_token();
    }
    
    auto* rule { consume_qualified_rule(input) };
    
    while (input.next_token().is_whitespace())
    {
        input.consume_next_token();
    }
    
    return rule;
}

template<typename T>
StyleSheet* parse_stylesheet(TokenStream<T>& input)
{
    auto* style_sheet { new StyleSheet };
    style_sheet->m_value = consume_list_of_rules(input);
    return style_sheet;
}

template<typename T>
SimpleSelector parse_simple_selector(TokenStream<T>& input)
{
    const auto& token_or_component_value { input.next_token() };
    
    if (const auto* token { token_or_component_value.token() }; token && token->is_ident())
    {
        return { SimpleSelector::Type::TagName, token->value() };
    }
    
    return { SimpleSelector::Type::Invalid };
}

}
