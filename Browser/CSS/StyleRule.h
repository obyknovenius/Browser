//
//  StyleRule.h
//  Browser
//
//  Created by Vitaly Dyachkov on 20.04.22.
//

#pragma once

#include "Selectors/SelectorList.h"
#include "Declaration.h"

namespace CSS {

class StyleRule
{
public:
    StyleRule(SelectorList selector_list, List<Declaration*> declarations);

private:
    SelectorList m_selector_list;
    List<Declaration*> m_declarations;
};

}
