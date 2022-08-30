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

std::vector<Fragment> TextRun::split(float remaining_fragmentainer_extent)
{
    std::vector<Fragment> fragments {};
    
    std::string line {};
    
    double line_width = remaining_fragmentainer_extent;
    
    double whitespace_width = m_font.width(" ");
    
    auto word_begin = m_text.begin();
    for (auto it = word_begin; it != m_text.end() ; ++it)
    {
        if (*it == ' ') {
            auto word = std::string(word_begin, it);
            auto word_width = m_font.width(word);
                        
            if (line_width < word_width)
            {
                fragments.push_back({ line });
                line = {};
                line_width = remaining_fragmentainer_extent;
            }
            
            line += word;
            line += " ";
            line_width -= (word_width + whitespace_width);
            
            word_begin = ++it;
        }
    }
    
    fragments.push_back({ line });

    return fragments;
}

}
