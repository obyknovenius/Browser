//
//  Fragment.h
//  Browser
//
//  Created by Vitaly Dyachkov on 15.07.22.
//

#pragma once

#include "../../Graphics/Font.h"
#include <string_view>

namespace CSS {

class Fragment final
{
public:
    Fragment(const std::string_view content, const Graphics::Font& font) : m_content { content }, m_font { font } {}
    
    const std::string_view content() const { return m_content; }
    
    const Graphics::Font& font() const { return m_font; }

private:
    std::string_view m_content;
    
    const Graphics::Font& m_font;
};

}
