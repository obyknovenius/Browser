/*
 * Tree.h
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

#include "../Infra/OrderedSet.h"
#include <cassert>

namespace DOM {

template <typename T>
class Tree final
{
public:
    Tree() = delete;

    class Object
    {
    public:
        T* parent() { return m_parent; }

        Infra::OrderedSet<T*>& children() { return m_children; }
        const Infra::OrderedSet<T*>& children() const { return m_children; }

        T* previous_sibling() { return m_previous_sibling; }
        const T* previous_sibling() const { return m_previous_sibling; }

        T* next_sibling() { return m_next_sibling; }
        const T* next_sibling() const { return m_next_sibling; }

    private:
        T* m_parent {};

        class Children final : public Infra::OrderedSet<T*>
        {
        public:
            Children(T* parent) : m_parent { parent } {}

            void append(T* child)
            {
                child->m_parent = m_parent;

                child->m_previous_sibling = this->m_items.back();
                this->m_items.back()->m_next_sibling = child;

                Infra::OrderedSet<T*>::append(child);
            }

        private:
            T* m_parent {};
        };

        Children m_children { this };

        T* m_previous_sibling { nullptr };
        T* m_next_sibling { nullptr };
    };
};

}
