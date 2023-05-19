/*
 * CodePoints.h
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

namespace Infra {

bool is_ascii_upper_alpha(int code_point)
{
    return code_point >= 'A' && code_point <= 'Z';
}

bool is_ascii_lower_alpha(int code_point)
{
    return code_point >= 'a' && code_point <= 'z';
}

bool is_ascii_alpha(int code_point)
{
    return is_ascii_upper_alpha(code_point) || is_ascii_lower_alpha(code_point);
}

}
