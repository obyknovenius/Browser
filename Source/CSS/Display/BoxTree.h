#pragma once

namespace CSS {
namespace BoxTree {

class Node
{
public:
    virtual ~Node() {}

    void set_parent(Node* parent);

    const Node* first_child() const { return m_first_child; }

private:
    Node* m_parent {};

    Node* m_first_child {};
    Node* m_last_child {};

    Node* m_previous_sibling {};
    Node* m_next_sibling {};
};

}
}