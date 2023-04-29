#include "BoxTree.h"

namespace CSS {
namespace BoxTree {

void Node::set_parent(Node* parent)
{
    m_parent = parent;

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
}