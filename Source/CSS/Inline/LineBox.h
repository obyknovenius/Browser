#pragma once

#include "../Break/Fragmentainer.h"

namespace CSS {

class LineBox final : public Fragmentainer
{
public:
    LineBox();

    virtual ~LineBox();

    virtual void add_fragment(const BoxFragment& fragment) override;
};

}