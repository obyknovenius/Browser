//
//  BlockBox.h
//  Browser
//
//  Created by Vitaly Dyachkov on 31.08.22.
//

#pragma once

#include "Box.h"
#include "../Inline/LineBox.h"
#include <vector>

namespace CSS {

class BlockBox : public Box
{
public:
    void layout(Graphics::Size size) override;
    
    void draw(const Graphics::Context &context) override;

private:
    std::vector<CSS::LineBox> m_line_boxes {};
};

}
