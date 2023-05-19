/*
 * Tokenizer.cpp
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

#include "Tokenizer.h"

#include <cstdio>

void Tokenizer::resume(TreeConstructor& tree_constructor)
{
    auto emit { [&tree_constructor](Token& token) { tree_constructor.handle(token); } };

    for (;;)
    {
        switch (m_state)
        {
            case State::Data:
            {
                char character { consume_next_input_character() };

                if (character == '<')
                {
                    switch_to(State::TagOpen);
                    break;
                }

                if (character == EOF)
                {
                    emit(EndOfFileToken {});
                    return;
                }

                emit(CharacterToken { m_input_stream.current_input_character() };
                break;
            }
        }
    }
}
