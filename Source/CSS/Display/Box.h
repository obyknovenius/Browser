#pragma once

#include "BoxTree.h"

#include <cairomm/cairomm.h>

namespace CSS {

class Box : public BoxTree::Node
{
public:
    Box(Cairo::RefPtr<Cairo::ScaledFont> font) : m_font { font } {}

    Cairo::RefPtr<Cairo::ScaledFont> font() const { return m_font; }

private:
    Cairo::RefPtr<Cairo::ScaledFont> m_font {};
};

}
