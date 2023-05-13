#pragma once

#include "../Display/Box.h"

#include <string>

namespace CSS {

class BoxFragment final
{
public:
    BoxFragment(const Box& box, const std::string& text, double width, double height)
        : m_box { box }
        , m_text { text }
        , m_width { width }
        , m_height { height }
    {}

    const Box& box() const { return m_box; }

    const std::string& text() const { return m_text; }

    double width() const { return m_width; }
    double height() const { return m_height; }

private:
    const Box& m_box;

    const std::string m_text {};

    const double m_width {};
    const double m_height {};
};

}
