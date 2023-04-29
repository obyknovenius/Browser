#pragma once

#include "Fragmentainer.h"

namespace CSS {

class FragmentationContext
{
    virtual ~FragmentationContext() {}

    virtual Fragmentainer& create_fragmentainer() = 0;
};

}