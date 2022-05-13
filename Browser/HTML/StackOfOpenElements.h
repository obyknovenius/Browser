//
//  StackOfOpenElements.h
//  Browser
//
//  Created by Vitaly Dyachkov on 16.03.22.
//

#pragma once

#include "../DOM/Element.h"
#include <deque>
#include <functional>

using namespace DOM;

namespace HTML {

class StackOfOpenElements
{
public:
    Element* topmost() { return m_deque.front(); }
    Element* bottommost() { return m_deque.back(); }
    
    void push(Element* element) { m_deque.push_back(element); }
    
    Element* pop()
    {
        auto* element { m_deque.back() };
        m_deque.pop_back();
        return element;
    }
    
    void pop_until(const std::function<bool(Element*)>& until);
    
    void pop_all() { m_deque.clear(); }

private:
    std::deque<Element*> m_deque {};
};

}
