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
    Node(std::shared_ptr<Document> node_document) : m_node_document { node_document } {}

    std::shared_ptr<Document> node_document() const { return m_node_document.lock(); }

    virtual const std::string node_name() const = 0;

private:
    std::weak_ptr<Document> m_node_document;
};

std::shared_ptr<Node> pre_insert(std::shared_ptr<Node> node, std::shared_ptr<Node> parent, std::shared_ptr<Node> child);
void insert(std::shared_ptr<Node> node, std::shared_ptr<Node> parent, std::shared_ptr<Node> child, bool suppress_observers_flag = false);
std::shared_ptr<Node> append(std::shared_ptr<Node> node, std::shared_ptr<Node> parent);

std::shared_ptr<DOM::Node> next(std::shared_ptr<DOM::Node>& current)
{
    return current->next_sibling();
}

}

