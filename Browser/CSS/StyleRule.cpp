//
//  StyleRule.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 20.04.22.
//

#include "StyleRule.h"

namespace CSS {

StyleRule::StyleRule(SelectorList selector_list, List<Declaration*> declarations)
    : m_selector_list { selector_list }
    , m_declarations { declarations }
{}

}
