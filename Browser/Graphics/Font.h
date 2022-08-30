//
//  Font.h
//  Browser
//
//  Created by Vitaly Dyachkov on 21.07.22.
//

#pragma once

#include <CoreText/CoreText.h>
#include <string>
#include <string_view>
#include <vector>

namespace Graphics {

class Font final
{
public:
    Font(const std::string& name, float size);
    ~Font();
    
    float ascent() const { return m_ascent; }
    float descent() const { return m_descent; }
            
    const CTFontRef ct_font() const { return m_ct_font; }
    
    double width(std::string_view text) const;
    
private:
    CTFontRef m_ct_font;
    
    float m_ascent;
    float m_descent;
};

}
