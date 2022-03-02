//
//  Tree.h
//  Browser
//
//  Created by Vitaly Dyachkov on 25.02.22.
//

#pragma once

#include <list>

namespace DOM::Tree {

template <typename T>
class Participant {
    T* m_parent {};
    std::list<T*> m_children {};
    
public:
    T* parent() { m_parent; }
    
    std::list<T*>& children() { return m_children; }
    
    T* root()
    {
        if (!parent()) {
            return this;
        }
        return root()->parent();
    }
};

}
