/*
 * List.h
 *
 * Copyright 2024 Vitaly Dyachkov <obyknovenius@me.com>
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

#include <cstddef>

namespace Infra {

template <typename Item>
class List
{
public:
    virtual ~List() = default;

    struct Iterator
    {
        explicit Iterator(Item* current) : m_current(current) {}

        Iterator& operator++()
        {
            if (m_current)
            {
                m_current = m_current->m_next;
            }
            return *this;
        }

        bool operator!=(const Iterator& other)
        {
            return m_current != other.m_current;
        }

        Item* operator*() const
        {
            return m_current;
        };

    private:
        Item* m_current;
    };

    size_t size() const { return m_size; }

    Item* first() const { return m_first; }
    Item* last() const { return m_last; }

    virtual void append(Item* item)
    {
        if (!m_size)
        {
            m_first = item;
            m_last = item;
        }
        else
        {
            item->m_previous = m_last;
            m_last->m_next = item;
            m_last = item;
        }
        ++m_size;
    }

    bool empty() const { return !m_size; }

    bool contains(Item* item) const
    {
        for (Item* current = m_first; current != nullptr; current = current->m_next)
        {
            if (current == item)
            {
                return true;
            }
        }
        return false;
    }

    Iterator begin() const { return Iterator { m_first }; }
    Iterator end() const { return Iterator { nullptr }; }

public:
    size_t m_size { 0 };

    Item* m_first {};
    Item* m_last {};
};

}
