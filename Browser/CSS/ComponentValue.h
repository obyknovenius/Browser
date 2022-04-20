//
//  ComponentValue.h
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#pragma once

#include "TokenStream.h"
#include "Token.h"
#include <string>
#include <list>

namespace CSS::Parser {

class SimpleBlock;

class ComponentValue final
{
    template<typename T>
    friend class TokenStream;
    
    template<typename T>
    friend ComponentValue consume_component_value(TokenStream<T>& input);

    friend std::ostream& operator<<(std::ostream& out, const ComponentValue& component_value);

public:
    const Token* token() const { return m_type == Type::PreservedToken ? &m_token : nullptr; }

private:
    enum class Type
    {
        Invalid,
        PreservedToken,
        SimpleBlock,
    };
    
    ComponentValue() = default;
    ComponentValue(const Token& token) : m_type { Type::PreservedToken }, m_token { token } {}
    ComponentValue(SimpleBlock* simple_block) : m_type { Type::SimpleBlock }, m_simple_block { simple_block } {}

    Type m_type { Type::Invalid };
    Token m_token {};
    SimpleBlock* m_simple_block { nullptr };
};

}
