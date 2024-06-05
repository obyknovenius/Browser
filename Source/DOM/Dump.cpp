/*
 * Dump.cpp
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

#include "Dump.h"

#include "Node.h"
#include "Text.h"

namespace DOM {

void dump_tree(const Node& root, int indent)
{
    for (int i = 0; i < indent; ++i)
    {
        std::cout << ' ';
    }

    if (const auto* text { dynamic_cast<const Text*>(&root) })
    {
        std::cout << text->data();
    }
    else
    {
        std::cout << root.node_name() << std::endl;
    }
    std::cout << std::endl;

    ++indent;
    if (!root.children().empty())
    {
        for (const auto* child : root.children())
        {
            dump_tree(*child, indent);
        }
    }
}

}
