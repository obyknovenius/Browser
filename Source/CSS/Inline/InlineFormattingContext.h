#pragma once

#include "../Display/FormattingContext.h"
#include "LineBox.h"

namespace CSS {

class InlineFormattingContext final : public FormattingContext
{
public:
    InlineFormattingContext();

    ~InlineFormattingContext();

    virtual LineBox& create_fragmentainer() override;
};

}