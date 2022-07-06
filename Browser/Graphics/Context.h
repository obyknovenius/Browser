//
//  Context.h
//  Browser
//
//  Created by Vitaly Dyachkov on 06.07.22.
//

#pragma once

#include <CoreGraphics/CoreGraphics.h>
#include <string_view>

namespace Graphics {

class Context final
{
public:
    Context(CGContextRef context);
    ~Context();
    
    void draw_text(std::string_view text);
    
private:
    CGContextRef m_context;
};

}
