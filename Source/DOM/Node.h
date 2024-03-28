/*
 * Node.h
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

#include "EventTarget.h"
#include "Tree.h"

namespace DOM {

class Document;

class Node : public Tree<Node>::Object, public EventTarget
{
public:
    Node(const Document& node_document) : m_node_document { node_document } {}

    const Document& node_document() const { return m_node_document; }

private:
    const Document& m_node_document;
};

Node& pre_insert(Node& node, Node& parent, Node* child);
void insert(Node& node, Node& parent, Node* child, bool suppress_observers_flag = false);
Node& append(Node& node, Node& parent);

}
