//
//  Token.h
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#pragma once

#include <string>
#include <string_view>
#include <iostream>

namespace CSS {

class Token final
{
    friend class Tokenizer;
    
public:
    Token() = default;
    
    bool is_whitespace() const { return m_type == Type::Whitespace; }
    bool is_left_curly_bracket() const { return m_type == Type::LeftCurlyBracket; }
    bool is_eof() const { return m_type == Type::EOF_; }
        
    friend std::ostream& operator<<(std::ostream& out, const Token& token);
    
private:
    enum class Type
    {
        Invalid,
        Indent,
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
    Token(Type type, std::string_view value) : m_type { type },  m_value { value } {}
    
    Type m_type { Type::Invalid };
    
    struct
    {
        std::string m_value {};
    };
};

}