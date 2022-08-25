//
//  Context.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 06.07.22.
//

#include "Context.h"
#include <CoreFoundation/CoreFoundation.h>
#include <CoreText/CoreText.h>
#include <iostream>

namespace Graphics {

Context::Context(CGContextRef cg_context)
{
    CFRetain(cg_context);
    m_cg_context = cg_context;
}

Context::~Context()
{
    CFRelease(m_cg_context);
}

void Context::draw_text(const std::string& text, const Font& font, int y) const
{
    CGContextSetTextMatrix(m_cg_context, CGAffineTransformMakeScale(1.0f, -1.0f));
    CGContextSetTextPosition(m_cg_context, 0, y + font.get_ascent());
    
    size_t count { text.size() };
    
    UniChar* characters { new UniChar[count] };
    for (long i { 0 }; i < count; i++) {
        characters[i] = text[i];
    }
    
    CTFontRef ct_font { font.ct_font() };
    
    CGGlyph* glyphs { new CGGlyph[count] };
    CTFontGetGlyphsForCharacters(ct_font, characters, glyphs, count);
    delete[] characters;
    
    CGSize* advances = { new CGSize[count] };
    CTFontGetAdvancesForGlyphs(ct_font, kCTFontOrientationHorizontal, glyphs, advances, count);
    
    CGPoint* positions { new CGPoint[count] };
    CGAffineTransform matrix { CGAffineTransformInvert(CGContextGetTextMatrix(m_cg_context)) };
    positions[0] = CGPointZero;
    for (int i { 1 }; i < count; ++i) {
        CGSize advance { CGSizeApplyAffineTransform(advances[i - 1], matrix) };
        positions[i].x = positions[i - 1].x + advance.width;
        positions[i].y = positions[i - 1].y + advance.height;
    }
    delete[] advances;

    CTFontDrawGlyphs(ct_font, glyphs, positions, count, m_cg_context);
    delete[] positions;
    delete[] glyphs;
}

}
