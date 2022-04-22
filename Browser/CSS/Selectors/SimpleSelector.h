//
//  SimpleSelector.h
//  Browser
//
//  Created by Vitaly Dyachkov on 14.04.22.
//

#pragma once

#include <string>

namespace CSS {

class SimpleSelector
{
public:
    enum class Type
    {
        Invalid,
        Type,
    };
    
    SimpleSelector(Type type) : m_type { type } {}
    SimpleSelector(Type type, const std::string_view identifier) : m_type { type }, m_identifier { identifier } {}

private:
    Type m_type;
    std::string m_identifier {};
};

}
