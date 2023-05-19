/*
 * Token.cpp
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

#include "Token.h"

namespace HTML {

std::ostream& operator<< (std::ostream& out, const Token& token)
{
    if (auto doctype_token = dynamic_cast<const DoctypeToken*>(&token))
    {
        std::cout << "<!DOCTYPE " << *doctype_token->name() << '>';
    }
    else if (auto start_tag_token = dynamic_cast<const StartTagToken*>(&token))
    {
        std::cout << '<' << start_tag_token->name() << '>';
    }
    else if (auto end_tag_token = dynamic_cast<const EndTagToken*>(&token))
    {
        std::cout << "</" << end_tag_token->name() << '>';
    }
    else if (auto comment_token = dynamic_cast<const CommentToken*>(&token))
    {
        std::cout << "<!--" << comment_token->data() << "-->";
    }
    else if (auto character_token = dynamic_cast<const CharacterToken*>(&token))
    {
        std::cout << character_token->data();
    }
    return out;
}

}
