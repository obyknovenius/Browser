//
//  Token.h
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#pragma once

#include <string>
#include <string_view>

namespace CSS {

class Token final
{
    friend class Tokenizer;
    
    friend std::ostream& operator<<(std::ostream& out, const Token& token);
    
public:
    enum class Type
    {
        Invalid,
        Ident,
        Delim,
        Whitespace,
        Colon,
        Semicolon,
        LeftCurlyBracket,
        RightCurlyBracket,
        EOF_,
    };
    
    Token() = default;
    Token(Type type) : m_type { type } {}
    Token(Type type, char value) : m_type { type },  m_value { value } {}
    Token(Type type, std::string_view value) : m_type { type },  m_value { value } {}
    
    bool is_ident() const { return m_type == Type::Ident; }
    bool is_whitespace() const { return m_type == Type::Whitespace; }
    bool is_left_curly_bracket() const { return m_type == Type::LeftCurlyBracket; }
    bool is_right_curly_bracket() const { return m_type == Type::RightCurlyBracket; }
    bool is_eof() const { return m_type == Type::EOF_; }
    
    bool is_ending(Token& token) const
    {
        return (m_type == Type::RightCurlyBracket && token.m_type == Type::LeftCurlyBracket);
    }
    
    std::string_view value() const { return m_value; }
    
private:
    Type m_type { Type::Invalid };
    
    std::string m_value {};
};

}
