//
//  Element.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 09.03.22.
//

#pragma once

#include "Node.h"
#include <string>

namespace DOM {

class Element : public Node
{
    friend Element* create_element(Document* document, const std::string& local_name, const std::string& namespace_);
    
protected:
    std::string to_string() const override;

private:
    std::string m_namespace;
    std::string m_local_name;
};

Element* create_element(Document* document, const std::string& local_name, const std::string& namespace_);

}
