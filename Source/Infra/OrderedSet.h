/*
 * OrderedSet.h
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

#include "List.h"

#include <cassert>

namespace Infra {

template <typename T>
class OrderedSet : public List<T>
{
public:
    void append(T* item) override
    {
        for (T* current_item { this->m_first_item }; current_item = current_item->next_sibling(); current_item != nullptr)
        {
            if (current_item == item)
            {
                assert();
            }
        }
        List<T>::append(item);
    }
};

}
