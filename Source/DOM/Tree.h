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

namespace DOM::Tree {

class Object
{
public:
    Object* parent() { return m_parent; }

    Infra::OrderedSet<Object*>& children() { return m_children; }

private:
    Object* m_parent {};

    class Children final : public Infra::OrderedSet<Object*>
    {
    public:
        Children(Object* parent) : m_parent { parent } {}

        void append(Object* child)
        {
            assert(!child->m_parent);
            child->m_parent = m_parent;
            Infra::OrderedSet<Object*>::append(child);
        }

    private:
        Object* m_parent {};
    };

    Children m_children { this };
};

}
