//
//  Fragment.h
//  Browser
//
//  Created by Vitaly Dyachkov on 15.07.22.
//

#pragma once

#include <string_view>

namespace CSS {

class Fragment final
{
public:
    Fragment(const std::string_view content) : m_content { content } {}
    
    const std::string_view content() const { return m_content; }

private:
    std::string_view m_content;
};

}
