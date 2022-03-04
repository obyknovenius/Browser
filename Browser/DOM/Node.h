//
//  Node.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.02.22.
//

#pragma once

#include "Tree.h"
#include <string>
#include <iostream>

namespace DOM {

class Node : public Tree<Node>::Participant
{
public:
    virtual ~Node() {}
    
    virtual std::string to_string() const = 0;
    
    friend void insert(Node* node, Node* parent, Node* child);
    friend Node* pre_insert(Node* node, Node* parent, Node* child);
    friend Node* append(Node* node, Node* parent);
    
    Node* insert_before(Node* node, Node* child);
    Node* append_child(Node* node);
    Node* replace_child(Node* node, Node* child);
    Node* remove_child(Node* child);
    
    friend std::ostream& operator<<(std::ostream& out, const Node& node);
};

void print_tree(const Node* root, int level = 0);

}
