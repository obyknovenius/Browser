#include "LineBox.h"

#include <algorithm>

namespace CSS {

void LineBox::add_fragment(const BoxFragment* fragment)
{
    Fragmentainer::add_fragment(fragment);
    m_height = std::max(m_height, fragment->height());
}

}
