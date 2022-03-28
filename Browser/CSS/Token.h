//
//  Token.h
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#pragma once

#include <string>
#include <iostream>

namespace CSS {

class Token final
{
    friend class Tokenizer;
    
public:
    Token() = default;
    
    bool is_eof() const { return m_type == Type::EOF_; }
    
    friend std::ostream& operator<<(std::ostream& out, const Token& token);
    
private:
    enum class Type
    {
        Invalid,
        Delim,
        Whitespace,
        Colon,
        Semicolon,
        LeftCurlyBracket,
        RightCurlyBracket,
        EOF_,
    };
    
    Token(Type type) : m_type { type } {}
    Token(Type type, char value) : m_type { type },  m_value { value } {}
    
    Type m_type { Type::Invalid };
    
    struct
    {
        std::string m_value {};
    };
};

}
