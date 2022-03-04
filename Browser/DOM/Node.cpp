//
//  Node.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.02.22.
//

#include "Node.h"
#include "Document.h"
#include "Comment.h"
#include "DocumentType.h"
#include <list>
#include <iostream>

namespace DOM {

std::ostream& operator<<(std::ostream& out, const Node& node)
{
    return out << node.to_string();
}

void insert(Node* node, Node* parent, Node* child)
{
    const std::list<Node*> nodes { node };
    
    auto count = nodes.size();
    if (count == 0)
    {
        return;
    }
    
    for (Node* node : nodes)
    {
        if (!child)
        {
            parent->children().append(node);
        }
    }
}

Node* pre_insert(Node* node, Node* parent, Node* child)
{
    auto* referenceChild = child;
    if (referenceChild == node)
    {
        referenceChild = node->next_sibling();
    }
    insert(node, parent, referenceChild);
    return node;
}

Node* append(Node* node, Node* parent)
{
    return pre_insert(node, parent, nullptr);
}

Node* Node::insert_before(Node* node, Node* child)
{
    return nullptr;
}

Node* Node::append_child(Node* node)
{
    return append(node, this);
}

Node* Node::replace_child(Node* node, Node* child)
{
    return nullptr;
}

Node* Node::remove_child(Node* child)
{
    return nullptr;
}

void print_tree(const Node* root, int level)
{
    for (int i {0}; i < level; ++i) {
        std::cout << ' ';
    }
    
    std::cout << *root << '\n';
        
    for (const Node* node { root->children().first() }; node; node = node->next()) {
        print_tree(node, level + 1);
    }
}

}
