/*
 * TreeConstructor.h
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

#include "Parser.h"
#include <optional>
#include <memory>

namespace DOM {

class Element;
class Node;

}

namespace HTML {

class Document;
class Token;

struct InsertionLocation
{
public:
    InsertionLocation(std::shared_ptr<DOM::Node> inside, std::shared_ptr<DOM::Node> before = nullptr)
        : m_inside { inside }
        , m_before { before }
    {}

    InsertionLocation(const InsertionLocation& other)
        : m_inside { other.m_inside }
        , m_before { other.m_before }
    {}

    std::shared_ptr<DOM::Node> inside() const { return m_inside; }
    std::shared_ptr<DOM::Node> before() const { return m_before; }

    std::shared_ptr<DOM::Node> immediately_before() { return m_before ? m_before->previous_sibling() : m_inside->last_child(); }

private:
    std::shared_ptr<DOM::Node> m_inside;
    std::shared_ptr<DOM::Node> m_before;
};

class TreeConstructor final
{
public:
    TreeConstructor(std::shared_ptr<Document> document, ParseState& parse_state)
        : m_document { document }
        , m_parse_state { parse_state }
    {}

    void dispatch(const Token& token);

private:
    InsertionLocation appropriate_place_for_inserting_node();
    std::shared_ptr<DOM::Element> create_element_for(const Token& token, const std::string& namespace_, std::shared_ptr<DOM::Node> intended_parent);
    void insert_element_at_adjusted_insertion_location(std::shared_ptr<DOM::Element> element);
    std::shared_ptr<DOM::Element> insert_foreign_element_for(const Token& token, const std::string& namespace_, bool only_add_to_element_stack);
    std::shared_ptr<DOM::Element> insert_html_element_for(const Token& token);
    void insert_character(const Token& token);
    void insert_comment(const Token& token, std::optional<InsertionLocation> position = std::nullopt);

    void process_using_rules_for(InsertionMode insertion_mode, const Token& token);

    void apply_rules_for_initial_insertion_mode(const Token& token);
    void apply_rules_for_before_html_insertion_mode(const Token& token);
    void apply_rules_for_before_head_insertion_mode(const Token& token);
    void apply_rules_for_in_head_insertion_mode(const Token& token);
    void apply_rules_for_after_head_insertion_mode(const Token& token);
    void apply_rules_for_in_body_insertion_mode(const Token& token);
    void apply_rules_for_after_body_insertion_mode(const Token& token);
    void apply_rules_for_after_after_body_insertion_mode(const Token& token);

    void reprocess(const Token& token) { process_using_rules_for(m_parse_state.insertion_mode, token); }

    void stop_parsing() { m_parse_state.parsing_stopped = true; }

    std::shared_ptr<Document> m_document;
    ParseState& m_parse_state;
};

}

