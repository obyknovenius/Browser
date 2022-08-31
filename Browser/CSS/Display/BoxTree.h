//
//  BoxTree.h
//  Browser
//
//  Created by Vitaly Dyachkov on 10.05.22.
//

#pragma once

#include "../../Graphics/Context.h"
#include "../../Graphics/Size.h"

namespace CSS {

class BoxTree
{
public:
    class Node
    {
    public:
        virtual ~Node() {}
        
        void set_parent(Node* parent);
        
        Node* first_child() { return m_first_child; }
        Node* last_child() { return m_last_child; }
        
        Node* previous_sibling() { return m_previous_sibling; }
        Node* next_sibling() { return m_next_sibling; }
        
        template<class T>
        T* is() { return dynamic_cast<T*>(this); }
        
        template<class T>
        const T* is() const { return dynamic_cast<const T*>(this); }
        
        virtual void layout(Graphics::Size size) {};
        
        virtual void draw(const Graphics::Context &context) {};
        
    private:
        Node* m_parent {};
        
        Node* m_first_child {};
        Node* m_last_child {};
        
        Node* m_previous_sibling {};
        Node* m_next_sibling {};
    };
    
private:
    BoxTree() = delete;
};

}
