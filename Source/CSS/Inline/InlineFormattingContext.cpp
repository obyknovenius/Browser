#include "InlineFormattingContext.h"

#include "LineBox.h"

namespace CSS {

void InlineFormattingContext::layout(double width)
{
    LineBox* line_box { new LineBox() };
    m_line_boxes.push_back(line_box);

    double remaining_fragmentainer_extent { width };
    while (m_fragmented_flow.has_next_fragment())
    {
        const BoxFragment* fragment { m_fragmented_flow.next_fragment(remaining_fragmentainer_extent) };
        if (!fragment)
        {
            remaining_fragmentainer_extent = width;
            line_box = new LineBox();
            m_line_boxes.push_back(line_box);
            continue;
        }
        line_box->add_fragment(fragment);
        remaining_fragmentainer_extent -= fragment->width();
    }
}

}