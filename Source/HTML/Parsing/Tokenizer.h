/*
 * Tokenizer.h
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

#include "InputStream.h"

#include <functional>

namespace HTML {

class Tokenizer final
{
public:
    Tokenizer(InputStream& input_stream) : m_input_stream { input_stream } {}

    void resume();

private:
    InputStream& m_input_stream;

    TreeConstructor& m_tree_constructor;

    enum class State
    {
        Data,
        TagOpen,
    };

    State m_state { State::Data };

    bool m_reconsume { false };

    char consume_next_input_character()
    {
        if (m_reconsume)
        {
            return m_input_stream.current_input_character();
        }
        return m_input_stream.next_input_character();
    }

    void reconsume_in_state(State state)
    {
        m_state = state;
        m_reconsume = true;
    }

    void emit(Token& token) { m_tree_constructor.handle(token); }
};

}
