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

#include <algorithm>
#include <list>

namespace Infra {

template <typename Item>
class List
{
public:
    virtual ~List() = default;

    virtual void append(Item item) { m_items.push_back(item); }

    bool contains(Item item) const { return std::find(m_items.cbegin(), m_items.cend(), item) != m_items.cend(); }

    size_t size() const { return m_items.size(); }

    bool is_empty() const { return m_items.empty(); }

    Item last() const { return m_items.back(); }

public:
    std::list<Item> m_items;
};

}
