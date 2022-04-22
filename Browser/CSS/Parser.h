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
#include "StyleRule.h"
#include "CSSStyleSheet.h"
#include "Selectors/SimpleSelector.h"
#include "Selectors/SelectorList.h"
#include "List.h"

namespace CSS {

template<typename T>
ComponentValue consume_component_value(TokenStream<T>& input);

template<typename T>
SimpleBlock* consume_simple_block(TokenStream<T>& input)
{
    auto* simple_block { new SimpleBlock { input.current_token() } };
    
    for (;;)
    {
        const auto& token { input.consume_next_token() };
        
        if (token.is_ending_token(simple_block->token()))
        {
            return simple_block;
        }
        else
        {
            input.reconsume();
            simple_block->value().push_back(consume_component_value(input));
        }
    }
}

template<typename T>
ComponentValue consume_component_value(TokenStream<T>& input)
{
    const auto& token { input.consume_next_token() };
    
    if (token.is_left_curly_bracket_token())
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
        
        if (token.is_left_curly_bracket_token())
        {
            qualified_rule->set_block(consume_simple_block(input));
            return qualified_rule;
        }
        else
        {
            input.reconsume();
            qualified_rule->prelude().push_back(consume_component_value(input));
        }
    }
}

template<typename T>
List<QualifiedRule*> consume_list_of_rules(TokenStream<T>& input)
{
    List<QualifiedRule*> list_of_rules {};
    
    for (;;)
    {
        const auto& token { input.consume_next_token() };
        
        if (token.is_whitespace_token())
        {
            // Do nothing.
        }
        else if (token.is_eof_token())
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
List<List<ComponentValue>> parse_comma_separated_list_of_component_values(TokenStream<T>& input)
{
    List<List<ComponentValue>> list_of_cvls {};
    
    ComponentValue component_value;
    do
    {
        List<ComponentValue> list {};
        for (;;)
        {
            component_value = consume_component_value(input);
            if (component_value.is_eof_token() || component_value.is_comma_token())
            {
                break;
            }
            list.push_back(component_value);
        }
        list_of_cvls.push_back(list);
        
    } while (component_value.is_comma_token());
    
    return list_of_cvls;
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
    style_sheet->set_value(consume_list_of_rules(input));
    return style_sheet;
}

template<typename T>
SimpleSelector parse_simple_selector(TokenStream<T>& input)
{
    const auto& token { input.next_token() };
    
    if (token.is_ident_token())
    {
        return { SimpleSelector::Type::Type, static_cast<Token>(token).value() };
    }
    
    return { SimpleSelector::Type::Invalid };
}

template<typename T>
SelectorList parse_selector_list(TokenStream<T>& input)
{
    SelectorList selector_list {};
    
    auto list_of_cvls = parse_comma_separated_list_of_component_values(input);
    for (const auto& list : list_of_cvls) {
        TokenStream<ComponentValue> tokens { list };
        SimpleSelector simple_selector { parse_simple_selector(tokens) };
        selector_list.push_back(simple_selector);
    }
    
    return selector_list;
}

StyleRule* interpret_as_style_rule(const QualifiedRule* rule);

template<typename T>
CSSStyleSheet* parse_css_stylesheet(TokenStream<T>& input)
{
    const auto* style_sheet { parse_stylesheet(input) };

    List<StyleRule*> style_rules {};
    for (const auto* rule : style_sheet->value())
    {
        auto* style_rule { interpret_as_style_rule(rule) };
        style_rules.push_back(style_rule);
    }
    
    return new CSSStyleSheet { style_rules };
}

}
