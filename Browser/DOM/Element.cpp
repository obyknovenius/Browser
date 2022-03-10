//
//  Element.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 09.03.22.
//

#include "Element.h"
#include "../HTML/HTMLElement.h"
#include <string_view>
#include <cassert>

namespace DOM {

std::string_view element_interface_for(std::string_view local_name, std::string_view namespace_)
{
    if (local_name == "html") {
        return "HTMLElement";
    }
    return {};
}

Element* create_element(Document* document, std::string_view local_name, std::string_view namespace_)
{
    Element* result { nullptr };
    
    std::string_view interface = element_interface_for(local_name, namespace_);
    
    if (interface == "HTMLElement") {
        result = new HTML::HTMLElement();
    }
    
    assert(result);
    return result;
}

}
