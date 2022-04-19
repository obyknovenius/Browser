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
    friend std::ostream& operator<<(std::ostream& out, const QualifiedRule& qualified_rule);
    
public:
    std::list<ComponentValue>& prelude() { return m_prelude; }
    const std::list<ComponentValue>& prelude() const { return m_prelude; }
    
    ComponentValue& block() { return m_block; }
    const ComponentValue& block() const { return m_block; }

private:
    std::list<ComponentValue> m_prelude {};
    ComponentValue m_block {};
};

}
