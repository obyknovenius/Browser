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
        Comma,
        LeftCurlyBracket,
        RightCurlyBracket,
        EOF_,
    };
    
    Token() = default;
    Token(Type type) : m_type { type } {}
    Token(Type type, char value) : m_type { type },  m_value { value } {}
    Token(Type type, std::string_view value) : m_type { type },  m_value { value } {}
    
    bool is_ident_token() const { return m_type == Type::Ident; }
    bool is_whitespace_token() const { return m_type == Type::Whitespace; }
    bool is_semicolon_token() const { return m_type == Type::Semicolon; }
    bool is_comma_token() const { return m_type == Type::Comma; }
    bool is_left_curly_bracket_token() const { return m_type == Type::LeftCurlyBracket; }
    bool is_right_curly_bracket_token() const { return m_type == Type::RightCurlyBracket; }
    bool is_eof_token() const { return m_type == Type::EOF_; }
    
    template<typename T>
    bool is_ending_token(const T& token) const
    {
        return token.is_left_curly_bracket_token() && is_right_curly_bracket_token();
    }
        
    std::string_view value() const { return m_value; }
    
private:
    Type m_type { Type::Invalid };
    
    std::string m_value {};
};

}
