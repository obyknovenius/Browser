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

class Document;

class Node : Tree<Node>::Participant
{
public:
    Node* parent() { return m_parent; }
    
    List<Node*>& children() { return m_children; }
    const List<Node*>& children() const { return m_children; }
    
    Node* root()
    {
        if (!parent())
        {
            return this;
        }
        return parent()->root();
    }
    
    Node* first_child() { return m_children.first_child(); }
    const Node* first_child() const { return m_children.first_child(); }
    
    Node* last_child() { return m_children.last_child(); }
    const Node* last_child() const { return m_children.last_child(); }
    
    Node* previous_sibling() { return m_previous_sibling; }
    const Node* previous_sibling() const { return m_previous_sibling; }
    
    Node* next_sibling() { return m_next_sibling; }
    const Node* next_sibling() const { return m_next_sibling; }
    
    Document* node_document() { return m_node_document; }
    
    friend void insert(Node* node, Node* parent, Node* child);
    friend Node* pre_insert(Node* node, Node* parent, Node* child);
    friend Node* append(Node* node, Node* parent);
    
    Node* insert_before(Node* node, Node* child);
    Node* append_child(Node* node);
    Node* replace_child(Node* node, Node* child);
    Node* remove_child(Node* child);
    
    virtual std::string to_string() const = 0;
    
    friend std::ostream& operator<<(std::ostream& out, const Node& node);
    
private:
    class Children : public List<Node*>
    {
        Node* m_parent { nullptr };
        Node* m_first_child { nullptr };
        Node* m_last_child { nullptr };
        
    public:
        Children(Node* parent) : m_parent { parent } {};
        
        Node* first_child() { return m_first_child; }
        const Node* first_child() const { return m_first_child; }
        
        Node* last_child() { return m_last_child; }
        const Node* last_child() const { return m_last_child; }
        
        void append(Node* node) override
        {
            node->m_parent = m_parent;
            
            if (!m_last_child)
            {
                m_first_child = node;
                m_last_child = node;
            }
            else
            {
                m_last_child->m_next_sibling = node;
                node->m_previous_sibling = m_last_child;
                m_last_child = node;
            }
        }
    };
        
    Node* m_parent { nullptr };
    Children m_children { this };
    
    Node* m_previous_sibling { nullptr };
    Node* m_next_sibling { nullptr };
    
    Document* m_node_document { nullptr };
};

void print_tree(const Node* root, int level = 0);

}
