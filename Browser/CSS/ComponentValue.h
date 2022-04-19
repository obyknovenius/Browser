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

class ComponentValue final
{    
    friend std::ostream& operator<<(std::ostream& out, const ComponentValue& component_value);

public:
    enum class Type
    {
        Invalid,
        PreservedToken,
        Function,
        SimpleBlock,
    };
    
    ComponentValue() = default;
    ComponentValue(Type type, const Token& token) : m_type { type }, m_token { token } {}
    ComponentValue(const Token& token) : m_type { Type::PreservedToken }, m_token { token } {}
    
    Token& token() { return m_token; }
    const Token& token() const { return m_token; }
    
    std::list<ComponentValue>& value() { return m_value; }
    const std::list<ComponentValue>& value() const { return m_value; }
    
    bool is_ident() const { return m_type == Type::PreservedToken && m_token.is_ident(); }
    
    operator Token() const { return m_token; };

private:
    Type m_type { Type::Invalid };
    Token m_token {};
    std::string m_name {};
    std::list<ComponentValue> m_value {};
};

}
