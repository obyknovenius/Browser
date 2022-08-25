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
    
    Graphics::Font font { "Helvetica", 24 };
         
    CGRect frame = self.frame;
    std::vector<std::string> lines = textRun->lines(font, frame.size.width);
    int y = 0;
    for (int i { 0 }; i < lines.size(); ++i)
    {
        const auto& line = lines.at(i);
        context.draw_text(line, font, y);
        y += 24;
    }
}

@end
