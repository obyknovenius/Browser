//
//  Parser.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#include "Parser.h"

namespace CSS {

StyleRule* interpret_as_style_rule(const QualifiedRule* rule)
{
    TokenStream<ComponentValue> tokens { rule->prelude() };
    SelectorList selector_list { parse_selector_list(tokens) };
    return new StyleRule { selector_list };
}

}
