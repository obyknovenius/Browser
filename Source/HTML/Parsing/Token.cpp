/*
 * Token.cpp
 *
 * Copyright 2023-2024 Vitaly Dyachkov <obyknovenius@me.com>
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

#include "Token.h"

namespace HTML {

std::ostream& operator<< (std::ostream& out, const Token& token)
{
    if (token.is_doctype())
    {
        if (token.name())
            return out << "<!DOCTYPE " << *token.name() << '>';
        else
            return out <<"!DOCTYPE>";
    }

    if (token.is_start_tag())
        return out << '<' << token.tag_name() << '>';

    if (token.is_end_tag())
        return out << "</" << token.tag_name() << '>';

    if (token.is_comment())
        return out << "<!--" << token.data() << "-->";

    if (token.is_character())
        return out << token.data();

    if (token.is_end_of_file())
        return out << "EOF";

    assert(false);

    return out;
}

}
