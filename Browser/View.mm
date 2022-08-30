//
//  View.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "View.h"
#import "CSS/Display/BoxTree.h"
#import "CSS/Display/TextRun.h"
#import "CSS/Inline/LineBox.h"
#import "CSS/Break/Fragment.h"
#import "CSS/Break/FragmentIterator.h"
#import "Graphics/Context.h"
#import <vector>

@implementation View

CSS::TextRun* textRun;

std::vector<CSS::LineBox> *lineBoxes;

- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self)
    {
        textRun = new CSS::TextRun("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam ac feugiat erat. Donec venenatis mattis rutrum. Curabitur id nisi vehicula lacus volutpat fringilla vitae eu est. Sed id ultricies ligula, non mattis nisi. Vestibulum blandit nisl id sem egestas eleifend. In porttitor maximus aliquam. Sed id aliquam dui. Aliquam a pretium elit. Phasellus pretium nisl vel mi efficitur ultrices.");
        lineBoxes = new std::vector<CSS::LineBox>();
    }
    return self;
}

- (void)dealloc
{
    delete textRun;
    delete lineBoxes;
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
    lineBoxes->clear();
    
    CSS::FragmentIterator it { textRun->text(), textRun->font() };
    
    while (std::optional<CSS::Fragment> fragment { it.next_fragment(self.frame.size.width) })
    {
        CSS::LineBox lineBox = CSS::LineBox();
        lineBox.append(*fragment);
        lineBoxes->push_back(lineBox);
    }
    
    [self setNeedsDisplay:YES];
}

- (void)drawRect:(NSRect)dirtyRect
{
    CGContextRef cgContext = [NSGraphicsContext currentContext].CGContext;
    Graphics::Context context { cgContext };
    
    const Graphics::Font& font = textRun->font();
    int y = 0;
    for (const CSS::LineBox& lineBox : *lineBoxes)
    {
        for (const CSS::Fragment& fragment : lineBox.fragments())
        {
            context.draw_text(fragment.content(), font, y);
        }
        y += (font.ascent() + font.descent());
    }
}

@end
