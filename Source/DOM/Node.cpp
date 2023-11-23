/*
 * Node.cpp
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

#include "Node.h"

#include "Element.h"

#include <list>

namespace DOM {

std::ostream& operator<<(std::ostream& out, const Node& node)
{
    return out << node.node_name();
}

// https://dom.spec.whatwg.org/#concept-node-pre-insert
Node* pre_insert(Node* node, Node* parent, Node* child)
{
    Node* referenceChild = child;
    if (referenceChild == node)
    {
        referenceChild = node->next_sibling();
    }
    insert(node, parent, referenceChild);
    return node;
}

// https://dom.spec.whatwg.org/#concept-node-insert
void insert(Node* node, Node* parent, Node* child)
{
    const std::list<Node*> nodes { node };

    std::size_t count = nodes.size();
    if (count == 0)
    {
        return;
    }

    for (Node* node : nodes)
    {
        if (!child)
        {
            parent->children().append(node);
        }
    }
}

//https://dom.spec.whatwg.org/#concept-node-append
Node* append(Node* node, Node* parent)
{
    return pre_insert(node, parent, nullptr);
}

}
