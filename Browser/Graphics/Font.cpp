//
//  Font.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.07.22.
//

#include "Font.h"

namespace Graphics {

Font::Font(const std::string& name, float size)
{
    CFStringRef cf_name { CFStringCreateWithCString(kCFAllocatorDefault, name.c_str(), kCFStringEncodingUTF8) };
    m_ct_font = CTFontCreateWithName(cf_name, size, NULL);
    CFRelease(cf_name);
    
    m_ascent = CTFontGetAscent(m_ct_font);
    m_descent = CTFontGetDescent(m_ct_font);
}

Font::~Font()
{
    CFRelease(m_ct_font);
}

double Font::width(std::string_view text) const
{
    size_t count { text.size() };
    
    UniChar* characters { new UniChar[count] };
    for (long i { 0 }; i < count; i++) {
        characters[i] = text[i];
    }
        
    CGGlyph* glyphs { new CGGlyph[count] };
    CTFontGetGlyphsForCharacters(m_ct_font, characters, glyphs, count);
    delete[] characters;
    
    CGSize* advances { new CGSize[count] };
    double total { CTFontGetAdvancesForGlyphs(m_ct_font, kCTFontOrientationHorizontal, glyphs, advances, count) };
    delete[] advances;
    delete[] glyphs;
    
    return total;
}

}
