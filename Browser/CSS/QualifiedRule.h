//
//  QualifiedRule.h
//  Browser
//
//  Created by Vitaly Dyachkov on 29.03.22.
//

#pragma once

#include "TokenStream.h"
#include "ComponentValue.h"
#include <list>

namespace CSS::Parser {

class SimpleBlock;

class QualifiedRule final
{
    template<typename T>
    friend QualifiedRule* consume_qualified_rule(TokenStream<T>& input);
    
    friend std::ostream& operator<<(std::ostream& out, const QualifiedRule& qualified_rule);
    
public:
    const std::list<ComponentValue>& prelude() const { return m_prelude; }
    const SimpleBlock* block() const { return m_block; }

private:
    QualifiedRule() = default;

    std::list<ComponentValue> m_prelude {};
    SimpleBlock* m_block { nullptr };
};

}
