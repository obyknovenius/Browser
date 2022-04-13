//
//  TokenStream.h
//  Browser
//
//  Created by Vitaly Dyachkov on 13.04.22.
//

#pragma once

#include "Token.h"
#include <list>
#include <iterator>

namespace CSS {

class TokenStream final
{
public:
    void push(const Token& token)
    {
        m_tokens.push_back(token);
        if (m_next == m_tokens.end())
        {
            m_next = m_tokens.begin();
        }
    }
    
    const Token& current_token() { return m_current; }
    const Token& next_token() { return *m_next; }
        
    const Token& consume_next_token()
    {
        m_current = *m_next;
        ++m_next;
        return m_current;
    }
    
    void reconsume() { --m_next; }
    
private:
    std::list<Token> m_tokens {};
    
    Token m_eof { Token::Type::EOF_ };
    
    Token& m_current { m_eof };
    
    std::list<Token>::const_iterator m_next { m_tokens.begin() };
};

}
