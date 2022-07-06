//
//  Context.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 06.07.22.
//

#include <CoreText/CoreText.h>
#include "Context.h"

namespace Graphics {

Context::Context(CGContextRef context)
{
    CFRetain(context);
    m_context = context;
}

Context::~Context()
{
    CFRelease(m_context);
}

void Context::draw_text(std::string_view text)
{
    CGContextSetTextMatrix(m_context, CGAffineTransformMakeScale(1.0f, -1.0f));
    
    CFStringRef string = CFStringCreateWithCString(NULL, text.data(), kCFStringEncodingUTF8);
    
    CFStringRef fontName = CFSTR("Helvetica");
    CGFloat fontSize = 24.0f;
    CTFontRef font = CTFontCreateWithName(fontName, fontSize, NULL);
    CFRelease(fontName);
    
    CFStringRef keys[] = { kCTFontAttributeName };
    CFTypeRef values[] = { font };
        
    CFDictionaryRef attributes = CFDictionaryCreate(NULL,
                                                    (const void**)&keys,
                                                    (const void**)&values,
                                                    sizeof(keys) / sizeof(keys[0]),
                                                    &kCFTypeDictionaryKeyCallBacks,
                                                    &kCFTypeDictionaryValueCallBacks);
    CFRelease(font);
    
    CFAttributedStringRef attrString = CFAttributedStringCreate(NULL, string, attributes);
    CFRelease(string);
    CFRelease(attributes);
    
    CTLineRef line = CTLineCreateWithAttributedString(attrString);
    CFRelease(attrString);
    
    CGContextSetTextPosition(m_context, 0, CTFontGetAscent(font));
    CTLineDraw(line, m_context);
    CFRelease(line);
}

}
