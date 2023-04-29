#pragma once

#include "BoxTree.h"
#include <string>

namespace CSS {

class TextSequence final : public BoxTree::Node
{
public:
    TextSequence(const std::string_view& text) : m_text { text } {}

    const std::string text() const { return m_text; }
private:
    std::string m_text;
};

}