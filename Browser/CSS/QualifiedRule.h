//
//  QualifiedRule.h
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#pragma once

#include "ComponentValue.h"
#include <list>

namespace CSS {

class QualifiedRule final
{
    friend class Parser;
    
    friend std::ostream& operator<<(std::ostream& out, const QualifiedRule& qualified_rule);
    
public:    
    const std::list<ComponentValue>& prelude() const { return m_prelude; }
    const ComponentValue& block() const { return m_block; }

private:
    std::list<ComponentValue> m_prelude {};
    ComponentValue m_block {};
};

}
