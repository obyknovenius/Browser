//
//  QualifiedRule.h
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#pragma once

#include "ComponentValue.h"
#include "SimpleBlock.h"
#include "List.h"

namespace CSS {

class SimpleBlock;

class QualifiedRule final
{
    friend std::ostream& operator<<(std::ostream& out, const QualifiedRule& qualified_rule);
    
public:
    List<ComponentValue>& prelude() { return m_prelude; }
    const List<ComponentValue>& prelude() const { return m_prelude; }
    
    SimpleBlock* block() { return m_block; }
    const SimpleBlock* block() const { return m_block; }
    void set_block(SimpleBlock* block) { m_block = block; }

private:
    List<ComponentValue> m_prelude {};
    SimpleBlock* m_block { nullptr };
};

}
