//
//  HTMLHtmlElement.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 10.03.22.
//

#pragma once

#include "HTMLElement.h"

namespace HTML {

class HTMLHtmlElement : public HTMLElement
{
public:
    std::string to_string() const override;
};

}
