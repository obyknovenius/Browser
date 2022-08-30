//
//  TextRun.h
//  Browser
//
//  Created by Vitaly Dyachkov on 10.05.22.
//

#pragma once

#include "BoxTree.h"
#include "../Break/Fragment.h"
#include "../../Graphics/Font.h"
#include <string>
#include <vector>

namespace CSS {

class TextRun : public BoxTree::Node
{
public:
    TextRun(std::string_view text) : m_text { text }, m_font { "Times", 16 } {}
    
    void draw(const Graphics::Context& context) override;
    
    const std::string& text() const { return m_text; }
    
    const Graphics::Font& font() const { return m_font; }
        
private:
    std::string m_text;
    
    Graphics::Font m_font;
};

}
