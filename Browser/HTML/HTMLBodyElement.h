//
//  HTMLBodyElement.h
//  Browser
//
//  Created by Vitaly Dyachkov on 16.03.22.
//

#pragma once

#include "HTMLElement.h"

namespace HTML {

class HTMLBodyElement : public HTMLElement
{
public:
    std::string to_string() const override;
};

}
