//
//  DocumentType.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 03.03.22.
//

#include "DocumentType.h"

namespace DOM {

std::string DocumentType::to_string() const
{
    return "DocumentType: " + m_name;
}

}
