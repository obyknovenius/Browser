//
//  View.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "View.h"
#import "Graphics/Context.h"

@implementation View

- (BOOL)isFlipped
{
    return YES;
}

- (void)drawRect:(NSRect)dirtyRect
{
    CGContextRef cgContext = [NSGraphicsContext currentContext].CGContext;
    
    CGContextSetTextMatrix(cgContext, CGAffineTransformMakeScale(1.0f, -1.0f));
    
    Graphics::Context context { cgContext };
    context.draw_text("Hello World!");
}

@end
