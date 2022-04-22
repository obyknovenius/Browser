//
//  CSSStyleSheet.h
//  Browser
//
//  Created by Vitaly Dyachkov on 20.04.22.
//

#pragma once

#include "StyleRule.h"
#include <vector>

namespace CSS {

class CSSStyleSheet
{
public:
    CSSStyleSheet(std::vector<StyleRule*> style_rules) : m_style_rules { style_rules } {}

private:
    std::vector<StyleRule*> m_style_rules;
};

}
