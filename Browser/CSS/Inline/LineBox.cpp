//
//  LineBox.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 15.07.22.
//

#include "LineBox.h"

namespace CSS
{

void LineBox::append(Fragment fragment)
{
    m_fragments.push_back(fragment);
}

}
