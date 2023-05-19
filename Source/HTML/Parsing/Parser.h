/*
 * Parser.h
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

#include "Tokenizer.h"
#include "TreeConstructor.h"

namespace HTML {

class Document;

class Parser final
{
public:
    Parser(std::ifstream& input_stream)
        : m_tokenizer { input_stream, m_tree_constructor }
    {}

    Document* parse();

private:
    Tokenizer m_tokenizer;
    TreeConstructor m_tree_constructor {};
};

}