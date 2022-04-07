//
//  StyleSheet.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 07.04.22.
//

#include "StyleSheet.h"
#include <iostream>

namespace CSS {

std::ostream& operator<<(std::ostream& out, const StyleSheet& stylesheet)
{
    for (auto& rule : stylesheet.m_value)
    {
        out << rule << '\n';
    }
    return out;
}

}
