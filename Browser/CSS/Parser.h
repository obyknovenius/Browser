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
#include <queue>
#include <list>

namespace CSS {

class Parser final
{
public:
    Parser(std::queue<Token>& tokens) : m_tokens { tokens } {}
    
    QualifiedRule parse_rule();
    
    ComponentValue consume_component_value();
    ComponentValue consume_simple_block();
    QualifiedRule consume_qualified_rule();
    
private:
    std::queue<Token>& m_tokens;
    
    Token m_eof_token { Token::Type::EOF_ };
    
    Token m_current_input_token {};
    
    bool m_reconsume { false };
    
    Token& next_input_token()
    {
        if (m_tokens.empty())
        {
            return m_eof_token;
        }
        return m_tokens.front();
    }
    
    Token& consume_next_input_token()
    {
        if (m_reconsume)
        {
            m_reconsume = false;
        }
        else
        {
            m_current_input_token = next_input_token();
            if (!m_tokens.empty())
            {
                m_tokens.pop();
            }
        }
        return m_current_input_token;
    }
    
    void reconsume_current_input_token()
    {
        m_reconsume = true;
    }
};

}
