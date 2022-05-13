//
//  StackOfOpenElements.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 16.03.22.
//

#include "StackOfOpenElements.h"

namespace HTML {

void StackOfOpenElements::pop_until(const std::function<bool(Element*)>& until)
{
    for (;;)
    {
        if (until(m_deque.back()))
        {
            return;
        }
        m_deque.pop_back();
    }
}

}
