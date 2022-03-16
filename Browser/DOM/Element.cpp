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
#include "../HTML/HTMLBodyElement.h"
#include "../HTML/HTMLHeadingElement.h"
#include <string_view>
#include <cassert>

using namespace Infra;
using namespace HTML;

namespace DOM {

Interface element_interface_for(std::string_view local_name, std::string_view namespace_)
{
    if (namespace_ == Namespace::HTML)
    {
        if (local_name == "html")
        {
            return Interface::HTMLHtmlElement;
        }
        else if (local_name == "head")
        {
            return Interface::HTMLHeadElement;
        }
        else if (local_name == "body")
        {
            return Interface::HTMLBodyElement;
        }
        else if (local_name == "h1" || local_name == "h2" || local_name == "h3"
                || local_name == "h4" || local_name == "h5" || local_name == "h6")
        {
            return Interface::HTMLHeadingElement;
        }
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
        case Interface::HTMLBodyElement:
        {
            result = new HTMLBodyElement();
            break;
        }
        case Interface::HTMLHeadingElement:
        {
            result = new HTMLHeadingElement();
            break;
        }
    }
    assert(result);
    return result;
}

}
