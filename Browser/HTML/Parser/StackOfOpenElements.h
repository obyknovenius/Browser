//
//  StackOfOpenElements.h
//  Browser
//
//  Created by Vitaly Dyachkov on 16.03.22.
//

#pragma once

#include "../../DOM/Element.h"
#include <deque>
#include <functional>

using namespace DOM;

namespace HTML {

class StackOfOpenElements
{
public:
    Element* topmost() { return m_queue.front(); }
    Element* bottommost() { return m_queue.back(); }
    
    void push(Element* element) { m_queue.push_back(element); }
    
    Element* pop()
    {
        auto* element { m_queue.back() };
        m_queue.pop_back();
        return element;
    }
    
    void pop_until(const std::function<bool(Element*)>& until);

private:
    std::deque<Element*> m_queue {};
};

}
