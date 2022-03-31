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

public:
    const std::string& namespace_() const { return m_namespace_; }
    const std::string& local_name() const { return m_local_name; }
    
    bool tag_name_is_one_of(std::initializer_list<std::string_view> tag_names) const;
    
protected:
    std::string to_string() const override;

private:
    std::string m_namespace_;
    std::string m_local_name;
};

Element* create_element(Document* document, const std::string& local_name, const std::string& namespace_);

}
