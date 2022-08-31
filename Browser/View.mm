//
//  View.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "View.h"
#import "CSS/Inline/LineBox.h"
#import "CSS/Break/Fragment.h"
#import "CSS/Break/FragmentIterator.h"
#import "Graphics/Context.h"
#import <vector>

@interface View ()

@property (readonly) std::vector<CSS::LineBox> *lineBoxes;

@end

@implementation View

- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self)
    {
        _lineBoxes = new std::vector<CSS::LineBox>();
    }
    return self;
}

- (void)dealloc
{
    delete _boxTree;
    delete _lineBoxes;
}

- (BOOL)wantsLayer
{
    return YES;
}

- (NSViewLayerContentsRedrawPolicy)layerContentsRedrawPolicy
{
    return NSViewLayerContentsRedrawOnSetNeedsDisplay;
}

- (BOOL)isFlipped
{
    return YES;
}

- (BOOL)preservesContentDuringLiveResize
{
    // This is an NSView method which we override to enable content
    // preservation in order to avoid flickering during a view resize.
    return YES;
}

- (void)layout
{
    self.boxTree->layout({ self.frame.size.width, self.frame.size.height});
    
    [self setNeedsDisplay:YES];
}

- (void)drawRect:(NSRect)dirtyRect
{
    CGContextRef cgContext = [NSGraphicsContext currentContext].CGContext;
    Graphics::Context context = Graphics::Context(cgContext);
    
    self.boxTree->draw(context);
}

@end
