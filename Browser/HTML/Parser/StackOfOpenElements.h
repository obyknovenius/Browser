//
//  StackOfOpenElements.h
//  Browser
//
//  Created by Vitaly Dyachkov on 16.03.22.
//

#pragma once

#include "../../DOM/Node.h"
#include <stack>

using namespace DOM;

namespace HTML {

class StackOfOpenElements
{
public:
    Node* bottommost() { return m_stack.top(); }
    
    void push(Node* element) { m_stack.push(element); }
    void pop() { m_stack.pop(); }

private:
    std::stack<Node*> m_stack {};
};

}
