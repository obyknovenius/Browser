//
//  Tree.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 04.03.22.
//

#pragma once

#include "../Infra/List.h"

namespace DOM {

using namespace Infra;

template <typename T>
class Tree
{
public:
    
    class Participant : public List<T>::Item
    {
        T* m_parent { nullptr };
        List<T> m_children {};
        
    public:
        T* parent() { return m_parent; }
        
        List<T>& children() { return m_children; }
        const List<T>& children() const { return m_children; }
        
        T* root()
        {
            if (!m_parent)
            {
                return this;
            }
            return m_parent->root();
        }
        
        T* first_child() { return m_children.first(); }
        T* last_child() { return m_children.last(); }
        
        T* previous_sibling() { return this->previous(); }
        T* next_sibling() { return this->next(); }
    };
};

}
