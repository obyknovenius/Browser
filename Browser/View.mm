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
    delete _textRun;
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
    self.lineBoxes->clear();
    
    CSS::FragmentIterator it = CSS::FragmentIterator(self.textRun->text(), self.textRun->font());
    
    while (std::optional<CSS::Fragment> fragment = it.next_fragment(self.frame.size.width))
    {
        CSS::LineBox lineBox = CSS::LineBox();
        lineBox.append(*fragment);
        self.lineBoxes->push_back(lineBox);
    }
    
    [self setNeedsDisplay:YES];
}

- (void)drawRect:(NSRect)dirtyRect
{
    CGContextRef cgContext = [NSGraphicsContext currentContext].CGContext;
    Graphics::Context context = Graphics::Context(cgContext);
    
    const Graphics::Font& font = self.textRun->font();
    int y = 0;
    for (const CSS::LineBox& lineBox : *self.lineBoxes)
    {
        for (const CSS::Fragment& fragment : lineBox.fragments())
        {
            context.draw_text(fragment.content(), font, y);
        }
        y += (font.ascent() + font.descent());
    }
}

@end
