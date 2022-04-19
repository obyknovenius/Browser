//
//  StyleSheet.h
//  Browser
//
//  Created by Vitaly Dyachkov on 07.04.22.
//

#pragma once

#include "QualifiedRule.h"
#include <list>

namespace CSS {

class StyleSheet
{
    friend std::ostream& operator<<(std::ostream& out, const StyleSheet& stylesheet);

public:
    std::list<QualifiedRule>& value() { return m_value; }
    const std::list<QualifiedRule>& value() const { return m_value; }
    
private:
    std::list<QualifiedRule> m_value;
};

}
