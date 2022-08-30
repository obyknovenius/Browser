//
//  View.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "View.h"
#import "CSS/Display/BoxTree.h"
#import "CSS/Display/TextRun.h"
#import "CSS/Break/Fragment.h"
#import "CSS/Break/FragmentIterator.h"
#import "Graphics/Context.h"

@implementation View

CSS::TextRun* textRun;

- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self)
    {
        textRun = new CSS::TextRun("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam ac feugiat erat. Donec venenatis mattis rutrum. Curabitur id nisi vehicula lacus volutpat fringilla vitae eu est. Sed id ultricies ligula, non mattis nisi. Vestibulum blandit nisl id sem egestas eleifend. In porttitor maximus aliquam. Sed id aliquam dui. Aliquam a pretium elit. Phasellus pretium nisl vel mi efficitur ultrices.");
    }
    return self;
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

- (void)drawRect:(NSRect)dirtyRect
{
    CGContextRef cgContext = [NSGraphicsContext currentContext].CGContext;
    Graphics::Context context { cgContext };
    
    const Graphics::Font& font = textRun->font();
        
    CSS::FragmentIterator it { textRun->text(), font };
    
    int y = 0;
    while (std::optional<CSS::Fragment> fragment { it.next_fragment(self.frame.size.width) })
    {
        context.draw_text(fragment->content(), font, y);
        y += (font.ascent() + font.descent());
    }
}

@end
