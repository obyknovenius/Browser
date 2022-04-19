//
//  SimpleSelector.h
//  Browser
//
//  Created by Vitaly Dyachkov on 14.04.22.
//

#pragma once

#include "TokenStream.h"
#include <optional>
#include <string>

namespace CSS {

class SimpleSelector
{
    friend SimpleSelector parse_simple_selector(TokenStream<Token>& input);

public:
    enum class Type
    {
        Invalid,
        TagName,
    };
    
    SimpleSelector(Type type) : m_type { type } {}
    SimpleSelector(Type type, const Token& token) : m_type { type }, m_identifier { token.value() } {}

private:
    Type m_type;
    std::string m_identifier {};
};

}
