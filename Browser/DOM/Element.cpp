//
//  Element.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 09.03.22.
//

#include "Element.h"
#include "../Infra/Namespace.h"
#include "../HTML/Interface.h"
#include "../HTML/HTMLHtmlElement.h"
#include "../HTML/HTMLHeadElement.h"
#include <string_view>
#include <cassert>

using namespace Infra;
using namespace HTML;

namespace DOM {

Interface element_interface_for(std::string_view local_name, std::string_view namespace_)
{
    if (local_name == "html" && namespace_ == Namespace::HTML)
    {
        return Interface::HTMLHtmlElement;
    }
    else if (local_name == "head" && namespace_ == Namespace::HTML)
    {
        return Interface::HTMLHeadElement;
    }
    assert(false);
    return {};
}

Element* create_element(Document* document, std::string_view local_name, std::string_view namespace_)
{
    Element* result { nullptr };
    Interface interface { element_interface_for(local_name, namespace_) };
    switch (interface)
    {
        case Interface::HTMLHtmlElement:
        {
            result = new HTMLHtmlElement();
            break;
        }

        case Interface::HTMLHeadElement:
        {
            result = new HTMLHeadElement();
            break;
        }
    }
    assert(result);
    return result;
}

}
