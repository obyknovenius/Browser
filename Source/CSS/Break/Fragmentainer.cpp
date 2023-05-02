#include "Fragmentainer.h"

namespace CSS {

void Fragmentainer::add_fragment(const BoxFragment* fragment)
{
    m_fragments.push_back(fragment);
}

}