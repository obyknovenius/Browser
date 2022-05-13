//
//  BoxTree.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 10.05.22.
//

#include "BoxTree.h"

namespace CSS {

void BoxTree::Node::set_parent(Node* parent)
{
    this->m_parent = parent;
    
    if (!parent->m_first_child)
    {
        parent->m_first_child = parent->m_last_child = this;
    }
    else
    {
        m_previous_sibling = parent->m_last_child;
        parent->m_last_child->m_next_sibling = this;
        parent->m_last_child = this;
    }
}

}
