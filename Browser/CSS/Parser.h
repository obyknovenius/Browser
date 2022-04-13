//
//  Parser.h
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#pragma once

#include "TokenStream.h"
#include "ComponentValue.h"
#include "QualifiedRule.h"
#include "StyleSheet.h"
#include <list>

namespace CSS {

class Parser final
{
public:
    Parser(TokenStream& input) : m_input { input } {}
    
    QualifiedRule parse_rule();
    StyleSheet parse_stylesheet();
    
private:
    TokenStream& m_input;
    
    ComponentValue consume_component_value();
    ComponentValue consume_simple_block();
    QualifiedRule consume_qualified_rule();
    std::list<QualifiedRule> consume_list_of_rules();
};

}
