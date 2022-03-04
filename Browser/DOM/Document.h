//
//  Document.h
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#pragma once

#include "Node.h"

namespace DOM {

class Document : public Node
{
public:
    std::string to_string() const override;
};

}
