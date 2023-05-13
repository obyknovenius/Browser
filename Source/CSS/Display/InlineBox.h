#pragma once

#include "Box.h"

#include <cairomm/cairomm.h>

namespace CSS {

class InlineBox final : public Box
{
public:
    InlineBox(Cairo::RefPtr<Cairo::ScaledFont> font) : Box { font } {}
};

}
