//
//  DocumentType.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 03.03.22.
//

#pragma once

#include "Node.h"
#include <string>

namespace DOM {

class DocumentType : public Node
{
public:
    DocumentType(std::string name) : m_name { name } {}
    
    const std::string& name() const { return m_name; }
    
    std::string to_string() const override;
    
private:
    std::string m_name {};
    std::string m_public_id {};
    std::string m_system_id {};
};

}
