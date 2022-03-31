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
    friend class Parser;
    friend class QualifiedRule;
    
    friend std::ostream& operator<<(std::ostream& out, const ComponentValue& component_value);

private:
    enum class Type
    {
        Invalid,
        PreservedToken,
        Function,
        SimpleBlock,
    };
    
    ComponentValue() = default;
    ComponentValue(Type type, Token token) : m_type { type }, m_token { token } {}
    ComponentValue(Token token) : m_type { Type::PreservedToken }, m_token { token } {}
    
    Type m_type { Type::Invalid };
    
    Token m_token {};
    
    std::string m_name {};
    
    std::list<ComponentValue> m_value {};
};

}
