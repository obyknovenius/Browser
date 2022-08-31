//
//  BlockBox.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 31.08.22.
//

#include "BlockBox.h"
#include "../Break/Fragment.h"
#include "../Break/FragmentIterator.h"
#include "../Display/TextRun.h"

namespace CSS {

void BlockBox::layout(Graphics::Size size)
{
    m_line_boxes.clear();
    
    for (Node* child { first_child() }; child; child = child->next_sibling())
    {
        if (auto* text_run { child->is<TextRun>() })
        {
            CSS::FragmentIterator it { text_run->text(), text_run->font() };
            
            while (std::optional<CSS::Fragment> fragment { it.next_fragment(size.width) })
            {
                CSS::LineBox line_box {};
                line_box.append(*fragment);
                m_line_boxes.push_back(line_box);
            }
        }
        else
        {
            child->layout(size);
        }
    }
}

void BlockBox::draw(const Graphics::Context &context)
{
    if (m_line_boxes.empty())
    {
        for (Node* child { first_child() }; child; child = child->next_sibling())
        {
            child->draw(context);
        }
        return;
    }
    
    int y = 0;
    for (const CSS::LineBox& line_box : m_line_boxes)
    {
        for (const CSS::Fragment& fragment : line_box.fragments())
        {
            const Graphics::Font& font { fragment.font() };
            context.draw_text(fragment.content(), font, y);
            y += (font.ascent() + font.descent());
        }
    }
}

}
