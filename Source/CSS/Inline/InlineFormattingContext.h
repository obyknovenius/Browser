#pragma once

#include "../Break/FragmentationContext.h"
#include "../Break/FragmentedFlow.h"
#include "../Display/FormattingContext.h"
#include "../Display/InlineBox.h"

#include <vector>

namespace CSS {

class LineBox;

class InlineFormattingContext final : public FormattingContext, public FragmentationContext
{
public:
    InlineFormattingContext(const InlineBox& root_inline_box, const Cairo::Context& context) : m_fragmented_flow { root_inline_box, context } {}

    void layout(double width);

    const std::vector<const LineBox*> line_boxes() const { return m_line_boxes; }

private:
    FragmentedFlow m_fragmented_flow;

    std::vector<const LineBox*> m_line_boxes {};
};

}