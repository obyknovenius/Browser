//
//  StyleSheet.h
//  Browser
//
//  Created by Vitaly Dyachkov on 07.04.22.
//

#pragma once

#include "QualifiedRule.h"
#include "List.h"

namespace CSS {

class StyleSheet
{
    friend std::ostream& operator<<(std::ostream& out, const StyleSheet& stylesheet);

public:
    List<QualifiedRule*>& value() { return m_value; }
    const List<QualifiedRule*>& value() const { return m_value; }
    void set_value(const List<QualifiedRule*>& value) { m_value = value; }
    
private:
    List<QualifiedRule*> m_value {};
};

}
