//
//  Fragment.h
//  Browser
//
//  Created by Vitaly Dyachkov on 15.07.22.
//

#pragma once

#include <string>

namespace CSS {

class Fragment final
{
public:
    Fragment(const std::string& content) : m_content { content } {}
    
    const std::string& content() const { return m_content; }

private:
    std::string m_content;
};

}
