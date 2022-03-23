//
//  Compatability.h
//  Browser
//
//  Created by Vitaly Dyachkov on 18.03.22.
//

#pragma once

#include "../DOM/Element.h"
#include "../Infra/Namespace.h"

using namespace DOM;

namespace HTML {

bool is_html_element(const Element& element)
{
    return element.namespace_() == Namespace::HTML;
}

}
