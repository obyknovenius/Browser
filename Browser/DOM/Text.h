//
//  Text.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 11.03.22.
//

#pragma once

#include "CharacterData.h"

namespace DOM {

class Text : public CharacterData
{
public:
    Text(const std::string& data = "")
    {
        m_data = data;
    }
    
    std::string to_string() const override;
};

}
