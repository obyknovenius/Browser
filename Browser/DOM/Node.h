//
//  Node.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.02.22.
//

#pragma once

#include <list>
#include "Tree.h"

namespace DOM {

class Node : public Tree::Participant<Node> {
    friend void insert(Node* node, Node* parent, Node* child);
    Node* pre_insert(Node* node, Node* parent, Node *child);

public:
    virtual ~Node() {}
    
    Node insert_efore(Node* node, Node* child);
    Node append_child(Node* node);
    Node replace_child(Node* node, Node* child);
    Node remove_child(Node* child);
};

void print_tree(const Node* root, int level = 0);

}
