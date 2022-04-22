//
//  StyleRule.h
//  Browser
//
//  Created by Vitaly Dyachkov on 20.04.22.
//

#pragma once

#include "Selectors/SelectorList.h"

namespace CSS {

class StyleRule
{
public:
    StyleRule(SelectorList selector_list) : m_selector_list { selector_list } {}

private:
    SelectorList m_selector_list;
};

}
