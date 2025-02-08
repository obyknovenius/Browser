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

namespace Infra {

template <typename Item>
class List
{
public:
    virtual ~List() = default;

    struct Iterator
    {
        Iterator(Item current) : m_current { current } {}

        Iterator& operator++()
        {
            if (m_current)
            {
                m_current = next(m_current);
                //m_current = m_current->m_next_sibling;
            }
            return *this;
        }

        bool operator!=(const Iterator& other)
        {
            return m_current != other.m_current;
        }

        Item operator*() const
        {
            return m_current;
        };

    private:
        Item m_current;
    };

    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;
};

}
