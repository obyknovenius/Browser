//
//  ComponentValue.h
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#pragma once

#include "Token.h"
#include <string>
#include <list>

namespace CSS {

class SimpleBlock;

class ComponentValue final
{
public:
    ComponentValue() = default;
    ComponentValue(const Token& token) : m_type { Type::PreservedToken }, m_token { token } {}
    ComponentValue(SimpleBlock* simple_block) : m_type { Type::SimpleBlock }, m_simple_block { simple_block } {}
    
    bool is_ident_token() const { return m_type == Type::PreservedToken && m_token.is_ident_token(); }
    bool is_whitespace_token() const { return m_type == Type::PreservedToken && m_token.is_whitespace_token(); }
    bool is_semicolon_token() const { return m_type == Type::PreservedToken && m_token.is_semicolon_token(); }
    bool is_comma_token() const { return m_type == Type::PreservedToken && m_token.is_comma_token(); }
    bool is_left_curly_bracket_token() const { return m_type == Type::PreservedToken && m_token.is_left_curly_bracket_token(); }
    bool is_right_curly_bracket_token() const { return m_type == Type::PreservedToken && m_token.is_right_curly_bracket_token(); }
    bool is_eof_token() const { return m_type == Type::PreservedToken && m_token.is_eof_token(); }
    
    template<typename T>
    bool is_ending_token(const T& token) const
    {
        return token.is_left_curly_bracket_token() && is_right_curly_bracket_token();
    }
    
    operator Token() const { return m_token; }
    
private:
    enum class Type
    {
        Invalid,
        PreservedToken,
        SimpleBlock,
    };

    Type m_type { Type::Invalid };
    Token m_token {};
    SimpleBlock* m_simple_block { nullptr };

    friend std::ostream& operator<<(std::ostream& out, const ComponentValue& component_value);
};

}

