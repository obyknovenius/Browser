/*
 * Parser.cpp
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

#include "Parser.h"

#include "Tokenizer.h"
#include "TreeConstructor.h"
#include "../Document.h"

namespace HTML {

Document* Parser::parse()
{
    Document* document { new Document {} };
    Tokenizer tokenizer { m_input_stream };
    TreeConstructor tree_constructor { *document, m_parse_state };

    while (!m_parse_state.parsing_stopped)
    {
        tree_constructor.dispatch(tokenizer.resume());
    }

    return tree_constructor.document();
}

}
