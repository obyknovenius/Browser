/*
 * Node.h
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

#include "../Infra/OrderedSet.h"

#include <iostream>
#include <string_view>

namespace DOM {

class Document;

class Node
{
public:
    Node(Document& node_document) : m_node_document { node_document } {}
    virtual ~Node() = default;

    virtual std::string_view node_name() const = 0;

    Document& node_document() { return m_node_document; }

    Infra::OrderedSet<Node>& children() { return m_children; }

    Node* first_child() { return m_children.first_item(); }
    Node* last_child() { return m_children.last_item(); }
    Node* previous_sibling() { return m_previous_sibling; }
    Node* next_sibling() { return m_next_sibling; }

    friend std::ostream& operator<<(std::ostream& out, const Node& node);

protected:
    Document& m_node_document;

private:
    friend class Infra::List<Node>;

    Node* m_parent_node;

    class Children : public Infra::OrderedSet<Node>
    {
    public:
        Children(Node* parent) : m_parent { parent } {}

        void append(Node* node) override
        {
            OrderedSet<Node>::append(node);
            node->m_parent_node = m_parent;
        }

    private:
        Node* m_parent;
    };
    Children m_children { this };

    Node* m_previous_sibling {};
    Node* m_next_sibling {};
};

Node* pre_insert(Node* node, Node* parent, Node* child);
void insert(Node* node, Node* parent, Node* child);
Node* append(Node* node, Node* parent);

}
