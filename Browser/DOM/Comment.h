//
//  Comment.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.02.22.
//

#pragma once

#include "Node.h"
#include <string>

namespace DOM {

class Comment : public Node {
    std::string m_data;
public:
    Comment(std::string data = "") : m_data { data } {}
};

}
