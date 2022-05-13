//
//  TextRun.h
//  Browser
//
//  Created by Vitaly Dyachkov on 10.05.22.
//

#pragma once

#include "BoxTree.h"
#include <string>
#include <string_view>

namespace CSS {

class TextRun : public BoxTree::Node
{
public:
    TextRun(std::string_view text) : m_text { text } {}
    
private:
    std::string m_text;
};

}
