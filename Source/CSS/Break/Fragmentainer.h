#pragma once

#include "BoxFragment.h"

namespace CSS {

class Fragmentainer
{
    virtual ~Fragmentainer();

    virtual void add_fragment(const BoxFragment& fragment) = 0;
};

}