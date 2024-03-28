/*
 * Token.h
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

#include <cassert>
#include <iostream>
#include <optional>
#include <string>

namespace HTML {

struct Token final
{
public:
    enum class Type
    {
        Invalid,
        Doctype,
        StartTag,
        EndTag,
        Comment,
        Character,
        EndOfFile,
    };

    Token() = default;
    Token(Type type) : m_type { type } {}
    Token(char character) : m_type { Type::Character }, m_data { character } {}

    bool is_doctype() const { return m_type == Type::Doctype; }
    bool is_start_tag() const { return m_type == Type::StartTag; }
    bool is_end_tag() const { return m_type == Type::EndTag; }
    bool is_tag() const { return m_type == Type::StartTag || m_type == Type::EndTag; }
    bool is_comment() const { return m_type == Type::Comment; }
    bool is_character() const { return m_type == Type::Character; }
    bool is_end_of_file() const { return m_type == Type::EndOfFile; }

    bool operator==(char character) const { return m_type == Type::Character && m_data.length() == 1 && m_data[0] == character; }

    std::string& name()
    {
        assert(is_doctype());
        assert(m_name);
        return *m_name;
    }

    const std::optional<std::string>& name() const
    {
        assert(is_doctype());
        return m_name;
    }

    void set_name(const std::string& name)
    {
        assert(is_doctype());
        m_name = name;
    }

    std::string& tag_name()
    {
        assert(is_start_tag() || is_end_tag());
        return m_tag_name;
    }

    const std::string& tag_name() const
    {
        assert(is_tag());
        return m_tag_name;
    }

    void set_tag_name(const std::string& tag_name)
    {
        assert(is_tag());
        m_tag_name = tag_name;
    }

    std::string& data()
    {
        assert(is_comment() || is_character());
        return m_data;
    }

    const std::string& data() const
    {
        assert(is_comment() || is_character());
        return m_data;
    }

    void set_data(const std::string& data)
    {
        assert(is_comment() || is_character());
        m_data = data;
    }

private:
    Type m_type { Type::Invalid };

    std::optional<std::string> m_name {};

    std::string m_tag_name {};

    std::string m_data {};

    friend std::ostream& operator<<(std::ostream& out, const Token& token);
};

}
