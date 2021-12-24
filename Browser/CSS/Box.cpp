//
//  Box.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#include "Box.h"

void Box::paint(CGContextRef context) {
    CGContextSetRGBFillColor (context, 1, 0, 0, 1);
    CGContextFillRect (context, CGRectMake (0, 0, 200, 100 ));
}
