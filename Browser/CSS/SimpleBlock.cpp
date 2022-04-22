//
//  SimpleBlock.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 19.04.22.
//

#include "SimpleBlock.h"
#include <iostream>

namespace CSS {

std::ostream& operator<<(std::ostream& out, const SimpleBlock& simple_block)
{
    out << "{\n";
    for (const auto& component_value : simple_block.m_value)
    {
        out << component_value;
    }
    return out << "\n}";
}

}
