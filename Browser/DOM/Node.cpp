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

void Node::Children::append(Node* node)
{
    node->m_parent = m_parent;
    
    if (!m_last)
    {
        m_first = node;
        m_last = node;
    }
    else
    {
        m_last->m_next_sibling = node;
        node->m_previous_sibling = m_last;
        m_last = node;
    }
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

std::ostream& operator<<(std::ostream& out, const Node& node)
{
    return out << node.to_string();
}

}
