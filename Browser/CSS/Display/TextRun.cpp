//
//  TextRun.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 10.05.22.
//

#include "TextRun.h"
#include <iostream>

namespace CSS {

void TextRun::draw(const Graphics::Context &context)
{
    context.draw_text(m_text, m_font, 0);
}

}
