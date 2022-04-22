//
//  SimpleBlock.h
//  Browser
//
//  Created by Vitaly Dyachkov on 19.04.22.
//

#pragma once

#include "Token.h"
#include "ComponentValue.h"
#include "List.h"

namespace CSS {

class SimpleBlock final
{
    friend std::ostream& operator<<(std::ostream& out, const SimpleBlock& simple_block);

public:
    SimpleBlock(const Token& token) : m_token { token } {}
    
    const Token& token() const { return m_token; }
    
    List<ComponentValue>& value() { return m_value; }
    const List<ComponentValue>& value() const { return m_value; }

private:
    Token m_token;
    List<ComponentValue> m_value {};
};

}
