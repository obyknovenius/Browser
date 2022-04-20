//
//  StyleSheet.h
//  Browser
//
//  Created by Vitaly Dyachkov on 07.04.22.
//

#pragma once

#include "TokenStream.h"
#include <list>

namespace CSS::Parser {

class QualifiedRule;

class StyleSheet
{
    template<typename T>
    friend StyleSheet* parse_stylesheet(TokenStream<T>& input);

    friend std::ostream& operator<<(std::ostream& out, const StyleSheet& stylesheet);

public:
    const std::list<QualifiedRule*>& value() const { return m_value; }
    
private:
    StyleSheet() = default;
    
    std::list<QualifiedRule*> m_value {};
};

}
