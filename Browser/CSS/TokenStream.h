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
    TokenStream(const std::list<Token>& tokens) : m_tokens { tokens } {}
    
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
    const std::list<Token> m_tokens {};
    
    Token m_eof { Token::Type::EOF_ };
    
    Token& m_current { m_eof };
    
    std::list<Token>::const_iterator m_next { m_tokens.begin() };
};

}
