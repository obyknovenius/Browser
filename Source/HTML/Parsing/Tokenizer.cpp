/*
 * Tokenizer.cpp
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

#include "Tokenizer.h"

#include "Token.h"
#include "../../Infra/Strings.h"
#include "../../Infra/CodePoints.h"

#include <cstdio>

namespace HTML {

std::string Tokenizer::next_few_characters(size_t count)
{
    std::string characters {};
    characters.resize(count);

    std::streampos position { m_input_stream.tellg() };
    m_input_stream.read(characters.data(), count);
    m_input_stream.seekg(position);

    m_those_characters_count = count;
    return characters;
}

void Tokenizer::consume_those_characters()
{
    for (size_t i { 0 }; i < m_those_characters_count; ++i)
    {
        consume_next_input_character();
    }
}

const Token Tokenizer::resume()
{
    for (;;)
    {
        switch (m_state)
        {
            case State::Data:
            {
                int curren_input_character { consume_next_input_character() };

                if (curren_input_character == '<')
                {
                    switch_to(State::TagOpen);
                    break;
                }

                if (curren_input_character == EOF)
                {
                    return { Token::Type::EndOfFile };
                }

                return { static_cast<char>(curren_input_character) };
            }
            case State::TagOpen:
            {
                int current_input_character { consume_next_input_character() };

                if (current_input_character == '!')
                {
                    switch_to(State::MarkupDeclarationOpen);
                    break;
                }

                if (current_input_character == '/')
                {
                    switch_to(State::EndTagOpen);
                    break;
                }

                if (Infra::is_ascii_alpha(current_input_character))
                {
                    auto& token { create_start_tag_token() };
                    token.tag_name() = "";
                    reconsume_in(State::TagName);
                    break;
                }
            }
            case State::EndTagOpen:
            {
                int current_input_character { consume_next_input_character() };

                if (Infra::is_ascii_alpha(current_input_character))
                {
                    auto& token { create_end_tag_token() };
                    token.tag_name() = "";
                    reconsume_in(State::TagName);
                    break;
                }
            }
            case State::TagName:
            {
                int current_input_character { consume_next_input_character() };

                if (current_input_character == '>')
                {
                    switch_to(State::Data);
                    return current_tag_token();
                }

                current_tag_token().tag_name() += static_cast<char>(current_input_character);
                break;
            }
            case State::MarkupDeclarationOpen:
            {
                if (next_few_characters(2) == "--")
                {
                    consume_those_characters();
                    create_comment_token("");
                    switch_to(State::CommentStart);
                    break;
                }

                if (Infra::is_ascii_case_insensitive_match(next_few_characters(7), "DOCTYPE"))
                {
                    consume_those_characters();
                    switch_to(State::Doctype);
                    break;
                }
            }
            case State::CommentStart:
            {
                int current_input_character { consume_next_input_character() };

                reconsume_in(State::Comment);
                break;
            }
            case State::Comment:
            {
                int current_input_character { consume_next_input_character() };

                if (current_input_character == '-')
                {
                    switch_to(State::CommentEndDash);
                    break;
                }

                current_comment_token().data() += static_cast<char>(current_input_character);
                break;
            }
            case State::CommentEndDash:
            {
                int current_input_character { consume_next_input_character() };

                if (current_input_character == '-')
                {
                    switch_to(State::CommentEnd);
                    break;
                }
            }
            case State::CommentEnd:
            {
                int current_input_character { consume_next_input_character() };

                if (current_input_character == '>')
                {
                    switch_to(State::Data);
                    return current_comment_token();
                }
            }
            case State::Doctype:
            {
                int current_input_character { consume_next_input_character() };

                if (current_input_character == '\t'
                || current_input_character == '\n'
                || current_input_character == '\f'
                || current_input_character == ' ')
                {
                    switch_to(State::BeforeDoctypeName);
                    break;
                }
            }
            case State::BeforeDoctypeName:
            {
                int current_input_character { consume_next_input_character() };

                if (current_input_character == '\t'
                || current_input_character == '\n'
                || current_input_character == '\f'
                || current_input_character == ' ')
                {
                    break;
                }

                if (Infra::is_ascii_upper_alpha(current_input_character))
                {
                    auto& token { create_doctype_token() };
                    token.name() = std::string { static_cast<char>(current_input_character + 0x0020) };
                    switch_to(State::DoctypeName);
                    break;
                }

                auto& token { create_doctype_token() };
                token.name() = std::string { static_cast<char>(current_input_character) };
                switch_to(State::DoctypeName);
                break;
            }
            case State::DoctypeName:
            {
                int current_input_character { consume_next_input_character() };

                if (Infra::is_ascii_upper_alpha(current_input_character))
                {
                    auto& token { create_doctype_token() };
                    token.name() = std::string { static_cast<char>(current_input_character + 0x0020) };
                    switch_to(State::DoctypeName);
                    break;
                }

                if (current_input_character == '>')
                {
                    switch_to(State::Data);
                    return current_doctype_token();
                }

                *current_doctype_token().name() += static_cast<char>(current_input_character);
                break;
            }
        }
    }
}

}
