//
//  Context.h
//  Browser
//
//  Created by Vitaly Dyachkov on 06.07.22.
//

#pragma once

#include "Font.h"
#include <CoreGraphics/CoreGraphics.h>
#include <string>

namespace Graphics {

class Context final
{
public:
    Context(CGContextRef cg_context);
    ~Context();
        
    void draw_text(const std::string& text, const Font& font, int y) const;
    
private:
    CGContextRef m_cg_context;
};

}
