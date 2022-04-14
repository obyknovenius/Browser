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
    friend SimpleSelector parse_simple_selector(TokenStream& input);

public:
    

private:
    enum class Type
    {
        Invalid,
        TagName,
    };
    
    SimpleSelector(Type type) : m_type { type } {}
    SimpleSelector(Type type, std::string_view identifier) : m_type { type }, m_identifier { identifier } {}
    
    Type m_type;
    std::string m_identifier {};
};

}
