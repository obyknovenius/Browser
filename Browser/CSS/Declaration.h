//
//  Declaration.h
//  Browser
//
//  Created by Vitaly Dyachkov on 22.04.22.
//

#pragma once

#include "ComponentValue.h"
#include "List.h"
#include <string>
#include <string_view>

namespace CSS {

class Declaration
{
public:
    Declaration(const std::string_view name) : m_name { name } {}
    
    List<ComponentValue>& value() { return m_value; }

private:
    std::string m_name;
    List<ComponentValue> m_value {};
    bool m_important { false };
};

}
