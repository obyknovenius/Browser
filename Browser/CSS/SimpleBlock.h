//
//  SimpleBlock.h
//  Browser
//
//  Created by Vitaly Dyachkov on 19.04.22.
//

#pragma once

#include "Token.h"
#include "ComponentValue.h"
#include <list>

namespace CSS::Parser {

class SimpleBlock
{
    template<typename T>
    friend SimpleBlock* consume_simple_block(TokenStream<T>& input);

    friend std::ostream& operator<<(std::ostream& out, const SimpleBlock& simple_block);

public:
    const Token& token() const { return m_token; }
    const std::list<ComponentValue>& value() const { return m_value; }

private:
    SimpleBlock(const Token& token) : m_token { token } {}

    Token m_token;
    std::list<ComponentValue> m_value {};
};

}
