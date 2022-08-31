//
//  FragmentIterator.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 30.08.22.
//

#include "FragmentIterator.h"

namespace CSS {

std::optional<Fragment> FragmentIterator::next_fragment(double remaining_fragmentainer_extent)
{
    double line_width = remaining_fragmentainer_extent;
    double space_width = m_font.width(" ");

    size_t line_begin = m_pos;
    size_t word_begin = m_pos;
    
    for (; m_pos <= m_fragmented_flow.length(); ++m_pos)
    {
        if (m_fragmented_flow[m_pos] == ' ' || m_fragmented_flow[m_pos] == '\0')
        {
            std::string_view word { m_fragmented_flow.data() + word_begin, m_pos - word_begin };
            double word_wdith = m_font.width(word);
            
            if (line_width < word_wdith)
            {
                ++m_pos;
                std::string_view line { m_fragmented_flow.data() + line_begin, word_begin - line_begin };
                return Fragment { line, m_font };
            }
            
            line_width -= (word_wdith + space_width);
            word_begin = ++m_pos;
        }
    }
    
    return {};
}

}
