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
    Graphics::Font font { "Helvetica", 24 };
    context.draw_text(m_text, font, 0);
}

std::vector<std::string> TextRun::lines(const Graphics::Font& font, float width)
{
    std::vector<std::string> lines {};
    
    std::string line {};
    
    double line_width = width;
    
    double whitespace_width = font.width(" ");
    
    auto word_begin = m_text.begin();
    for (auto it = word_begin; it != m_text.end() ; ++it)
    {
        if (*it == ' ') {
            auto word = std::string(word_begin, it);
            auto word_width = font.width(word);
                        
            if (line_width < word_width)
            {
                lines.push_back(line);
                line = {};
                line_width = width;
            }
            
            line += word;
            line += " ";
            line_width -= (word_width + whitespace_width);
            
            word_begin = ++it;
        }
    }
    
    lines.push_back(line);

    return lines;
}

}
