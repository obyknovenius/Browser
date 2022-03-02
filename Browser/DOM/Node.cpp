//
//  Node.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.02.22.
//

#include "Node.h"

namespace DOM {

void insert(Node* node, Node* parent, Node* child)
{
    const std::list<Node*>& nodes { node };
    
    auto count = nodes.size();
    if (count == 0) {
        return;
    }
    
    for (Node* node : nodes) {
        if (!child) {
            parent->children().push_back(node);
        }
    }
}

}
