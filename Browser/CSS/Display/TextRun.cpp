//
//  TextRun.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 10.05.22.
//

#include "TextRun.h"

namespace CSS {

void TextRun::draw(Graphics::Context &context)
{
    context.draw_text(m_text);
}

}
