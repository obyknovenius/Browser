/*
 * Token.h
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

#include <iostream>
#include <optional>

namespace HTML {

class Token
{
public:
    virtual ~Token() = default;

    friend std::ostream& operator<< (std::ostream& out, const Token& token);
};

class DoctypeToken final : public Token
{
public:
    std::optional<std::string>& name() { return m_name; }
    const std::optional<std::string>& name() const { return m_name; }
    void set_name(const std::string& name) { m_name = name; }

private:
    std::optional<std::string> m_name;
};

class TagToken : public Token
{
public:
    std::string& name() { return m_name; }
    const std::string& name() const { return m_name; }
    void set_name(const std::string& name) { m_name = name; }

private:
    std::string m_name;
};

class StartTagToken final : public TagToken
{
};

class EndTagToken final : public TagToken
{
};

class CommentToken final : public Token
{
public:
    CommentToken(const std::string& data) : m_data { data } {}

    std::string& data() { return m_data; }
    const std::string& data() const { return m_data; }

private:
    std::string m_data;
};

class CharacterToken final : public Token
{
public:
    CharacterToken(char data) : m_data { data } {}

    char data() const { return m_data; }

private:
    char m_data;
};

class EndOfFileToken final : public Token
{
};

}
