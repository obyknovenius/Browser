#pragma once

#include "BoxFragment.h"

#include <vector>

namespace CSS {

class Fragmentainer
{
public:
    virtual ~Fragmentainer() = default;

    virtual void add_fragment(const BoxFragment* fragment);

    const std::vector<const BoxFragment*>& fragments() const { return m_fragments; }

protected:
    std::vector<const BoxFragment*> m_fragments {};  
};

}
