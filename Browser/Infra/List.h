//
//  List.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 04.03.22.
//

#pragma once

namespace Infra {

template <typename T>
class List
{
    T* m_first { nullptr };
    T* m_last { nullptr };
    
public:
    class Item
    {
        friend class List;
        
        T* m_previous { nullptr };
        T* m_next { nullptr };
        
    public:
        T* previous() { return m_previous; }
        const T* previous() const { return m_previous; }
        
        T* next() { return m_next; }
        const T* next() const { return m_next; }
    };
    
    T* first() { return m_first; }
    const T* first() const { return m_first; }
    
    T* last() { return m_last; }
    const T* last() const { return m_last; }
    
    void append(T* item)
    {
        if (!m_last)
        {
            m_first = m_last = item;
        }
        else
        {
            m_last->m_next = item;
        }
    }
};

}
