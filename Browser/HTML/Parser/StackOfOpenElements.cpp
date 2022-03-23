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
        if (until(m_queue.back()))
        {
            return;
        }
        m_queue.pop_back();
    }
}

}
