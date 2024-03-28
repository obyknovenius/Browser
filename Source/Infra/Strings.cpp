/*
 * Strings.cpp
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

#include "Strings.h"

#include <algorithm>
#include <cctype>

namespace Infra {

std::string ascii_lowercase(const std::string& string)
{
    std::string lowercase_string { string };
    std::transform(lowercase_string.begin(),
                   lowercase_string.end(),
                   lowercase_string.begin(),
                   [](unsigned char character) { return std::tolower(character); });
    return lowercase_string;
}

std::string ascii_uppercase(const std::string& string)
{
    std::string uppercase_string { string };
    std::transform(uppercase_string.begin(),
                   uppercase_string.end(),
                   uppercase_string.begin(),
                   [](unsigned char character) { return std::toupper(character); });
    return uppercase_string;
}

bool is_ascii_case_insensitive_match(const std::string& a, const std::string& b)
{
    return ascii_lowercase(a) == ascii_lowercase(b);
}

}
