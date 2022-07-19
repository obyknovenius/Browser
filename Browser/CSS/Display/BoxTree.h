//
//  BoxTree.h
//  Browser
//
//  Created by Vitaly Dyachkov on 10.05.22.
//

#pragma once

#include "../../Graphics/Context.h"

namespace CSS {

class BoxTree
{
public:
    class Node
    {
    public:
        virtual ~Node() {}
        
        void set_parent(Node* parent);
        
        virtual void draw(Graphics::Context &context) = 0;
        
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
