/*
 * StackOfOpenElements.h
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

#include <deque>

namespace DOM {

class Element;

}

namespace HTML {

class StackOfOpenElements
{
public:
    DOM::Element* topmost() { return m_deque.front(); }
    DOM::Element* bottommost() { return m_deque.back(); }

    void push(DOM::Element* element) { m_deque.push_back(element); }

private:
    std::deque<DOM::Element*> m_deque;
};

}
