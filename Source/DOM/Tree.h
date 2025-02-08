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

#include "../Infra/List.h"
#include <cassert>
#include <iostream>
#include <memory>

namespace DOM {

template <typename T>
class Tree final
{
public:
    Tree() = delete;

    class Object : public std::enable_shared_from_this<T>
    {
    public:
        virtual ~Object() {}

        class Children final : public Infra::List<std::shared_ptr<T>>
        {
        public:
            Children(std::shared_ptr<T> parent) : m_parent { parent } {}

            Children(std::shared_ptr<const T> parent) : m_parent { std::const_pointer_cast<T>(parent) } {}

            Infra::List<std::shared_ptr<T>>::Iterator begin() { return { m_parent->m_first_child }; }
            Infra::List<std::shared_ptr<T>>::Iterator end() { return { nullptr }; }

            bool empty() const
            {
                return !m_parent->m_first_child;
            }

            void append(std::shared_ptr<T> child)
            {
                child->m_parent = m_parent;
                if (!m_parent->m_first_child)
                {
                    m_parent->m_first_child = child;
                    m_parent->m_last_child = child;
                }
                else
                {
                    child->m_previous_sibling = m_parent->m_last_child;
                    m_parent->m_last_child->m_next_sibling = child;
                    m_parent->m_last_child = child;
                }
            }

            void append(std::shared_ptr<T> child) const { assert(false); }

        private:
            std::shared_ptr<T> m_parent;
        };

        std::weak_ptr<T> parent() { return m_parent; }

        Children children() { return Children { this->shared_from_this() }; }
        const Children children() const { return Children { this->shared_from_this() }; }

        std::shared_ptr<T> first_child() { return m_first_child; }
        const std::shared_ptr<T> first_child() const { return m_first_child; }

        std::shared_ptr<T> last_child() { return m_last_child; }
        const std::shared_ptr<T> last_child() const { return m_last_child; }

        std::shared_ptr<T> previous_sibling() { return m_previous_sibling; }
        const std::shared_ptr<T> previous_sibling() const { return m_previous_sibling; }

        std::shared_ptr<T> next_sibling() { return m_next_sibling; }
        const std::shared_ptr<T> next_sibling() const { return m_next_sibling; }

    protected:
        Object() = default;

    private:
        std::weak_ptr<T> m_parent {};

        std::shared_ptr<T> m_first_child {};
        std::shared_ptr<T> m_last_child {};

        std::shared_ptr<T> m_previous_sibling {};
        std::shared_ptr<T> m_next_sibling {};
    };
};

}

