#pragma once

#include <string>

namespace CSS {

class BoxFragment final
{
public:
    BoxFragment(const std::string& text) : m_text { text } {};

    const std::string& text() const { return m_text; }

private:
    std::string m_text;
};

}