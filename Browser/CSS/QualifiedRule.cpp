//
//  QualifiedRule.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#include "QualifiedRule.h"
#include "SimpleBlock.h"
#include <iostream>

namespace CSS::Parser {

std::ostream& operator<<(std::ostream& out, const QualifiedRule& qualified_rule)
{
    for (auto token : qualified_rule.m_prelude)
    {
        out << token;
    }
    return out << *qualified_rule.m_block;
}

}
