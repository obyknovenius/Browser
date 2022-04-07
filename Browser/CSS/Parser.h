//
//  Parser.h
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#pragma once

#include "Token.h"
#include "ComponentValue.h"
#include "QualifiedRule.h"
#include "StyleSheet.h"
#include <queue>
#include <list>

namespace CSS {

class Parser final
{
public:
    Parser(std::queue<Token>& tokens) : m_tokens { tokens } {}
    
    QualifiedRule parse_rule();
    StyleSheet parse_stylesheet();
    
private:
    std::queue<Token>& m_tokens;
    
    const Token m_eof_token { Token::Type::EOF_ };
    
    Token m_current_input_token {};
    bool m_reconsume { false };
    
    const Token& next_input_token();
    const Token& consume_next_input_token();
    void reconsume_current_input_token() { m_reconsume = true; }
    
    ComponentValue consume_component_value();
    ComponentValue consume_simple_block();
    QualifiedRule consume_qualified_rule();
    std::list<QualifiedRule> consume_list_of_rules();
};

}
