//
//  View.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "View.h"
#import "CSS/Display/BoxTree.h"
#import "CSS/Display/TextRun.h"
#import "Graphics/Context.h"

@implementation View

CSS::BoxTree::Node* boxTree;

- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self)
    {
        boxTree = new CSS::TextRun("Hello World");
    }
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}

- (void)drawRect:(NSRect)dirtyRect
{
    CGContextRef cgContext = [NSGraphicsContext currentContext].CGContext;
    
    CGContextSetTextMatrix(cgContext, CGAffineTransformMakeScale(1.0f, -1.0f));
    
    Graphics::Context context { cgContext };
    
    boxTree->draw(context);
}

@end
