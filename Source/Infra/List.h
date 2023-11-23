/*
 * List.h
 *
 * Copyright 2023 Vitaly Dyachkov <obyknovenius@me.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

namespace Infra {

template <typename T>
class List
{
public:
    virtual ~List() = default;

    struct Iterator
    {
        Iterator(T* item) : m_item { item } {}

        T& operator*() const { return *m_item; }
        T* operator->() { return m_item; }

        Iterator& operator++()
        {
            m_item = m_item->m_next_sibling;
            return *this;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_item == b.m_item; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_item != b.m_item; };

        private:
            T* m_item;
    };

    Iterator begin() { return Iterator { m_first_item }; }
    Iterator end()   { return Iterator { m_last_item }; }

    T* first_item() { return m_first_item; }
    T* last_item() { return m_last_item; }

    virtual void append(T* item)
    {
        if (!m_last_item)
        {
            m_first_item = item;
            m_last_item = item;
        }
        else
        {
            item->m_previous_sibling = m_last_item;
            m_last_item->m_next_sibling = item;
            m_last_item = item;
        }
    }

protected:
    T* m_first_item {};
    T* m_last_item {};
};

}

