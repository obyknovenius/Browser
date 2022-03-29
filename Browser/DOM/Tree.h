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
    Tree() = delete;
    
    class Participant
    {
    public:
        virtual ~Participant() {}
        
        virtual T* parent() = 0;
        
        virtual List<T*>& children() = 0;
        virtual const List<T*>& children() const = 0;
        
        virtual T* root() = 0;
        
        virtual T* first_child() = 0;
        virtual const T* first_child() const = 0;
        
        virtual T* last_child() = 0;
        virtual const T* last_child() const = 0;
        
        virtual T* previous_sibling() = 0;
        virtual const T* previous_sibling() const = 0;
        
        virtual T* next_sibling() = 0;
        virtual const T* next_sibling() const = 0;
    };
};

}
