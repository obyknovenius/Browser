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

std::vector<Fragment> TextRun::split(double remaining_fragmentainer_extent)
{
    std::vector<Fragment> fragments {};
        
    double line_width = remaining_fragmentainer_extent;
    double space_width = m_font.width(" ");

    size_t line_begin = 0;
    size_t word_begin = 0;
    
    for (size_t i { 0 }; i <= m_text.length(); ++i)
    {
        if (m_text[i] == ' ' || m_text[i] == '\0')
        {
            std::string_view word { m_text.data() + word_begin, i - word_begin };
            double word_wdith = m_font.width(word);
            if (line_width < word_wdith)
            {
                std::string_view line { m_text.data() + line_begin, word_begin - line_begin };
                fragments.push_back({ line });
                line_begin = word_begin;
                line_width = remaining_fragmentainer_extent;
            }
            line_width -= (word_wdith + space_width);
            word_begin = ++i;
        }
    }
    
    return fragments;
}

}
