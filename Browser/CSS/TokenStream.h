//
//  TokenStream.h
//  Browser
//
//  Created by Vitaly Dyachkov on 13.04.22.
//

#pragma once

#include "Token.h"
#include "List.h"
#include <iterator>

namespace CSS {

template<typename T>
class TokenStream final
{
public:
    TokenStream(const List<T>& tokens) : m_tokens { tokens } {}
    
    const T& current_token() { return m_current; }
    const T& next_token()
    {
        if (m_next == m_tokens.end())
        {
            return m_eof;
        }
        return *m_next;
    }
        
    const T& consume_next_token()
    {
        m_current = next_token();
        ++m_next;
        return m_current;
    }
    
    void reconsume() { --m_next; }
    
private:
    const List<T>& m_tokens {};
    
    const T m_eof { Token::Type::EOF_ };
    
    T m_current { m_eof };
    
    typename List<T>::const_iterator m_next { m_tokens.begin() };
};

}
