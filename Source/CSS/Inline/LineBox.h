#pragma once

#include "../Break/Fragmentainer.h"

namespace CSS {

class LineBox final : public Fragmentainer
{
public:
    void add_fragment(const BoxFragment* fragment) override;

    double height() const { return m_height; }
private:
    double m_height {};
};

}
