//
//  Element.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 09.03.22.
//

#pragma once

#include "Node.h"

namespace DOM {

class Element : public Node
{
};

Element* create_element(Document* document, std::string_view local_name, std::string_view namespace_);

}
