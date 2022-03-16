//
//  Text.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 11.03.22.
//

#include "Text.h"

namespace DOM {

std::string Text::to_string() const
{
    return "Text: " + m_data;
}

}
