//
//  QualifiedRule.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#include "QualifiedRule.h"
#include <iostream>

namespace CSS {

std::ostream& operator<<(std::ostream& out, const QualifiedRule& qualified_rule)
{
    for (auto token : qualified_rule.m_prelude)
    {
        out << token;
    }
    return out << qualified_rule.m_block;
}

}
