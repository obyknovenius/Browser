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

#include "TreeConstructor.h"

#include <fstream>

namespace HTML {

class Tokenizer final
{
public:
    Tokenizer(std::ifstream& input_stream, TreeConstructor& tree_constructor)
      : m_input_stream { input_stream }
      , m_tree_constructor { tree_constructor }
    {}

    void resume();

private:
    std::ifstream& m_input_stream;

    TreeConstructor& m_tree_constructor;

    enum class State
    {
        Data,
        TagOpen,
        EndTagOpen,
        TagName,
        BeforeAttributeName,
        AttributeName,
        AfterAttributeName,
        BeforeAttributeValue,
        AttributeValueDoubleQuoted,
        AttributeValueSingleQuoted,
        AttributeValueUnquoted,
        AfterAttributeValueQuoted,
        MarkupDeclarationOpen,
        CommentStart,
        CommentStartDash,
        Comment,
        CommentEndDash,
        CommentEnd,
        CommentEndBang,
        Doctype,
        BeforeDoctypeName,
        DoctypeName,
        AfterDoctypeName,
        AfterDoctypePublicKeyword,
        BeforeDoctypePublicIdentifier,
        DoctypePublicIdentifierDoubleQuoted,
        DoctypePublicIdentifierSingleQuoted,
        AfterDoctypePublicIdentifier,
        BetweenDoctypePublicAndSystemIdentifiers,
        AfterDoctypeSystemKeyword,
        BeforeDoctypeSystemIdentifier,
        DoctypeSystemIdentifierDoubleQuoted,
        DoctypeSystemIdentifierSingleQuoted,
        AfterDoctypeSystemIdentifier,
        BogusDoctype,
    };

    State m_state { State::Data };

    size_t m_those_characters_count {};

    Token* m_current_token {};

    void switch_to_state(State state) { m_state = state; }

    int consume_next_input_character() { return m_input_stream.get(); }

    void reconsume_in_state(State state)
    {
        m_input_stream.unget();
        m_state = state;
    }

    std::string next_few_characters(size_t count);
    void consume_those_characters();

    template <typename T, typename... Args>
    T* create_token(Args... args)
    {
        T* current_token = new T(args...);
        m_current_token = current_token;
        return current_token;
    }

    template <typename T>
    T* current_token() { return dynamic_cast<T*>(m_current_token); }

    void emit(const Token& token) { m_tree_constructor.handle(token); }
};

}
