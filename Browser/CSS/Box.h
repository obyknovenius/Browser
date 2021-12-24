//
//  Box.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#pragma once

#include <CoreGraphics/CoreGraphics.h>

struct Thickness {
    float top { 0 };
    float right { 0 };
    float bottom { 0 };
    float left { 0 };
};

class Box {
public:
    void paint(CGContextRef);
private:
    Thickness padding;
    Thickness border;
    Thickness margin;
};
