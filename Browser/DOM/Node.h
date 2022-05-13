//
//  Node.h
//  Browser
//
//  Created by Vitaly Dyachkov on 25.02.22.
//

#pragma once

#include "../Infra/List.h"
#include <string>
#include <iostream>

namespace DOM {

using namespace Infra;

class Document;

class Node
{
public:
    Node* parent() { return m_parent; }
    const Node* parent() const { return m_parent; }
    
    List<Node*>& children() { return m_children; }
    const List<Node*>& children() const { return m_children; }
    
    Node* root() { return m_parent ? m_parent->root() : this; }
    const Node* root() const { return m_parent ? m_parent->root() : this; }
    
    Node* first_child() { return m_children.first(); }
    const Node* first_child() const { return m_children.first(); }
    
    Node* last_child() { return m_children.last(); }
    const Node* last_child() const { return m_children.last(); }
    
    Node* previous_sibling() { return m_previous_sibling; }
    const Node* previous_sibling() const { return m_previous_sibling; }
    
    Node* next_sibling() { return m_next_sibling; }
    const Node* next_sibling() const { return m_next_sibling; }
    
    Document* node_document() { return m_node_document; }
    
    template<class T>
    T* is() { return dynamic_cast<T*>(this); }
    
    template<class T>
    const T* is() const { return dynamic_cast<const T*>(this); }
    
    virtual std::string to_string() const = 0;
    
    friend std::ostream& operator<<(std::ostream& out, const Node& node);
    
private:
    class Children final : public List<Node*>
    {
    public:
        Children(Node* parent) : m_parent { parent } {}
        
        void append(Node* node) override;
        
        Node* first() { return m_first; }
        const Node* first() const { return m_first; }
        
        Node* last() { return m_last; }
        const Node* last() const { return m_last; }
        
    private:
        Node* m_parent {};
        Node* m_first {};
        Node* m_last {};
    };
    
    Node* m_parent {};
    Children m_children { this };
    
    Node* m_previous_sibling {};
    Node* m_next_sibling {};
    
    Document* m_node_document {};
};

void insert(Node* node, Node* parent, Node* child);
Node* pre_insert(Node* node, Node* parent, Node* child);
Node* append(Node* node, Node* parent);

}
