//
//  CharacterData.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 11.03.22.
//

#pragma once

#include "Node.h"
#include <string>
#include <string_view>

namespace DOM {

class CharacterData : public Node
{
public:
    std::string& data() { return m_data; }
    const std::string& data() const { return m_data; }
    
protected:
    std::string m_data {};
};

}
