#pragma once

#include <string>

namespace CSS {

class BoxFragment final
{
public:
    BoxFragment(const std::string& text, double width) : m_text { text }, m_width { width } {}

    const std::string& text() const { return m_text; }

    double width() const { return m_width; }

private:
    std::string m_text {};

    double m_width {};
};

}