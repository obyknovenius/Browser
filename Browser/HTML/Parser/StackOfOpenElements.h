//
//  StackOfOpenElements.h
//  Browser
//
//  Created by Vitaly Dyachkov on 16.03.22.
//

#pragma once

#include "../../DOM/Element.h"
#include <stack>
#include <functional>

using namespace DOM;

namespace HTML {

class StackOfOpenElements
{
public:
    Element* bottommost() { return m_stack.top(); }
    
    void push(Element* element) { m_stack.push(element); }
    
    Element* pop()
    {
        auto* element { m_stack.top() };
        m_stack.pop();
        return element;
    }
    
    void pop_until(const std::function<bool(Element*)>& until);

private:
    std::stack<Element*> m_stack {};
};

}
