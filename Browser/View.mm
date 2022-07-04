//
//  View.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "View.h"

@implementation View

- (BOOL)isFlipped
{
    return YES;
}

- (void)drawRect:(NSRect)dirtyRect
{
    CGContextRef context = [NSGraphicsContext currentContext].CGContext;
    
    CGContextSetTextMatrix(context, CGAffineTransformMakeScale(1.0f, -1.0f));
    
    CFStringRef string = CFSTR("Hello World!");
    
    CFStringRef fontName = CFSTR("Helvetica");
    CGFloat fontSize = 24.0f;
    CTFontRef font = CTFontCreateWithName(fontName, fontSize, NULL);
    CFRelease(fontName);
    
    CFStringRef keys[] = { kCTFontAttributeName };
    CFTypeRef values[] = { font };
    
    CFDictionaryRef attributes = CFDictionaryCreate(NULL, (const void**)&keys,
                                                    (const void**)&values, sizeof(keys) / sizeof(keys[0]),
                                                    &kCFTypeDictionaryKeyCallBacks,
                                                    &kCFTypeDictionaryValueCallBacks);
    CFRelease(font);
    
    CFAttributedStringRef attrString = CFAttributedStringCreate(NULL, string, attributes);
    CFRelease(string);
    CFRelease(attributes);
    
    CTLineRef line = CTLineCreateWithAttributedString(attrString);
    CFRelease(attrString);
    
    CGContextSetTextPosition(context, 0, CTFontGetAscent(font));
    CTLineDraw(line, context);
    CFRelease(line);
}

@end
