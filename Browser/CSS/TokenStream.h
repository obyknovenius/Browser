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

template<typename T>
class TokenStream final
{
public:
    TokenStream(const std::list<T>& tokens) : m_tokens { tokens } {}
    
    const T& current_token() { return m_current; }
    const T& next_token() { return *m_next; }
        
    const T& consume_next_token()
    {
        m_current = *m_next;
        ++m_next;
        return m_current;
    }
    
    void reconsume() { --m_next; }
    
private:
    const std::list<T>& m_tokens {};
    
    T m_eof { Token::Type::EOF_ };
    
    T& m_current { m_eof };
    
    typename std::list<T>::const_iterator m_next { m_tokens.begin() };
};

}
