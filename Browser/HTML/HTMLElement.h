//
//  HtmlElement.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 09.03.22.
//

#pragma once

#include "../DOM/Element.h"

namespace HTML {

class HTMLElement : public DOM::Element
{
public:
    std::string to_string() const override;
};

}
