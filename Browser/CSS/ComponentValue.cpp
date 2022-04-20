//
//  ComponentValue.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#include "ComponentValue.h"
#include "SimpleBlock.h"
#include <iostream>

namespace CSS::Parser {

std::ostream& operator<<(std::ostream& out, const ComponentValue& component_value)
{
    switch (component_value.m_type) {
        case ComponentValue::Type::Invalid:
        {
            break;
        }
        case ComponentValue::Type::PreservedToken:
        {
            out << component_value.m_token;
            break;
        }
        case ComponentValue::Type::SimpleBlock:
        {
            out << *component_value.m_simple_block;
            break;
        }
    }
    return out;
}

}
