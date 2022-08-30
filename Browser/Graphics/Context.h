//
//  Context.h
//  Browser
//
//  Created by Vitaly Dyachkov on 06.07.22.
//

#pragma once

#include "Font.h"
#include <CoreGraphics/CoreGraphics.h>
#include <string_view>

namespace Graphics {

class Context final
{
public:
    Context(CGContextRef cg_context);
    ~Context();
        
    void draw_text(const std::string_view text, const Font& font, int y) const;
    
private:
    CGContextRef m_cg_context;
};

}
