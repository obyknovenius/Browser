//
//  TextRun.h
//  Browser
//
//  Created by Vitaly Dyachkov on 10.05.22.
//

#pragma once

#include "BoxTree.h"
#include "../../Graphics/Font.h"
#include <string>
#include <vector>

namespace CSS {

class TextRun : public BoxTree::Node
{
public:
    TextRun(std::string_view text) : m_text { text } {}
    
    void draw(const Graphics::Context& context) override;
    
    const std::string& text() const { return m_text; }
    
    std::vector<std::string> lines(const Graphics::Font& font, float width);
        
private:
    std::string m_text;
};

}
