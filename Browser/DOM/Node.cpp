//
//  Node.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.02.22.
//

#include "Node.h"
#include "Document.h"
#include "Comment.h"
#include <iostream>

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

void print_tree(const Node* root, int level)
{
    for (int i {0}; i < level; ++i) {
        std::cout << ' ';
    }
    
    if (const auto* document = dynamic_cast<const Document*>(root)) {
        std::cout << "Document";
    }
    
    if (const auto* comment = dynamic_cast<const Comment*>(root)) {
        std::cout << "Comment";
    }
    
    std::cout << '\n';
    
    for (const Node* node : root->children()) {
        print_tree(node, level + 1);
    }
}

}
