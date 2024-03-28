/*
 * Tokenizer.h
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

#pragma once

#include "Token.h"
#include "TreeConstructor.h"
#include <cassert>
#include <fstream>

namespace HTML {

class Tokenizer final
{
public:
    Tokenizer(std::ifstream& input_stream) : m_input_stream { input_stream } {}

    const Token resume();

private:
    std::ifstream& m_input_stream;

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

    void switch_to_state(State state) { m_state = state; }

    int consume_next_input_character() { return m_input_stream.get(); }

    void reconsume_in_state(State state)
    {
        m_input_stream.unget();
        m_state = state;
    }

    std::string next_few_characters(size_t count);
    void consume_those_characters();

    Token& current_doctype_token()
    {
        assert(m_current_token.is_doctype());
        return m_current_token;
    }

    Token& current_tag_token()
    {
        assert(m_current_token.is_tag());
        return m_current_token;
    }

    Token& current_comment_token()
    {
        assert(m_current_token.is_comment());
        return m_current_token;
    }

    Token& create_doctype_token()
    {
        m_current_token = { Token::Type::Doctype };
        return m_current_token;
    }

    Token& create_start_tag_token()
    {
        m_current_token = { Token::Type::StartTag };
        return m_current_token;
    }

    Token& create_end_tag_token()
    {
        m_current_token = { Token::Type::EndTag };
        return m_current_token;
    }

    Token& create_comment_token(const std::string& data)
    {
        m_current_token = { Token::Type::Comment };
        m_current_token.set_data(data);
        return m_current_token;
    }

    Token m_current_token;
};

}
