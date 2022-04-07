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
    friend class Parser;
    
    friend std::ostream& operator<<(std::ostream& out, const StyleSheet& stylesheet);

private:
    std::list<QualifiedRule> m_value;
};

}
