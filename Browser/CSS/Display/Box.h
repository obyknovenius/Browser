//
//  Box.h
//  Browser
//
//  Created by Vitaly Dyachkov on 18.07.22.
//

#pragma once

#include "BoxTree.h"

namespace CSS {

class Box : public BoxTree::Node
{
public:
    void draw(const Graphics::Context &context) override;
};

}
