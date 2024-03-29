/*
 * Node.cpp
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

#include "Node.h"

#include <list>

namespace DOM {

Node& pre_insert(Node& node, Node& parent, Node* child)
{
    auto* referenceChild { child };

    if (referenceChild == &node)
        referenceChild = node.next_sibling();

    insert(node, parent, referenceChild);
    return node;
}

void insert(Node& node, Node& parent, Node* child, bool suppress_observers_flag)
{
    const std::list<Node*> nodes { &node };

    auto count { nodes.size() };
    if (count == 0)
        return;

    for (auto* node : nodes)
    {
        if (!child)
            parent.children().append(node);
    }
}

Node& append(Node& node, Node& parent)
{
    return pre_insert(node, parent, nullptr);
}

}
