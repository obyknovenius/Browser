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
    TokenStream<ComponentValue> prelude_tokens { rule->prelude() };
    SelectorList selector_list { parse_selector_list(prelude_tokens) };
    
    TokenStream<ComponentValue> block_tokens { rule->block()->value() };
    List<Declaration*> declarations { parse_style_block_contents(block_tokens) };
                                                            
    return new StyleRule { selector_list, declarations };
}

}
