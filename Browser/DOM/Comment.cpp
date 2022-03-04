//
//  Comment.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.02.22.
//

#include "Comment.h"

namespace DOM {

std::string Comment::to_string() const
{
    return "Comment: " + m_data;
}

}
