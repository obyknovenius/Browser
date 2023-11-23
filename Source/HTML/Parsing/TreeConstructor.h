/*
 * TreeConstructor.h
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

#include "../../DOM/Document.h"

#include <optional>
#include <stack>
#include <string>

namespace DOM {

class Element;
class Node;

}

namespace HTML {

class CharacterToken;
class CommentToken;
class TagToken;
class Token;

struct InsertionLocation
{
    DOM::Node* inside {};
    DOM::Node* before {};
};

class TreeConstructor final
{
public:
    TreeConstructor(DOM::Document& document) : m_document { document } {}

    void dispatch(const Token& next_token);

private:
    DOM::Document& m_document;

    enum class InsertionMode
    {
        Initial,
        BeforeHtml,
        BeforeHead,
        InHead,
        AfterHead,
        InBody,
        AfterBody,
        AfterAfterBody
    };

    InsertionMode m_insertion_mode { InsertionMode::Initial };

    // https://html.spec.whatwg.org/multipage/parsing.html#stack-of-open-elements
    std::stack<DOM::Node*> m_stack_of_open_elements {};

    // https://html.spec.whatwg.org/multipage/parsing.html#the-element-pointers
    DOM::Element* m_head_element_pointer {};
    DOM::Element* m_form_element_pointer {};

    // https://html.spec.whatwg.org/multipage/parsing.html#other-parsing-state-flags
    enum class FramesetOkFlag
    {
        Ok,
        NotOk,
    };

    FramesetOkFlag m_frameset_ok_flag { FramesetOkFlag::Ok };

    void switch_to(InsertionMode insertion_mode) { m_insertion_mode = insertion_mode; }

    DOM::Node* current_node() { return m_stack_of_open_elements.top(); }

    DOM::Element* create_element_for(const TagToken& token, const std::string& namespace_, DOM::Node* intended_parent);

    DOM::Element* insert_foreign_element_for(const TagToken& token, const std::string& namespace_);
    DOM::Element* insert_html_element_for(const TagToken& token);

    InsertionLocation appropriate_place_for_inserting_node();

    void insert_character(const CharacterToken& token);
    void insert_comment(const CommentToken& token, std::optional<InsertionLocation> position = std::nullopt);

    void process_using_rules_for(InsertionMode insertion_mode, const Token& token);
    void reprocess(const Token& token) { process_using_rules_for(m_insertion_mode, token); }

    void apply_rules_for_initial_insertion_mode(const Token& token);
    void apply_rules_for_before_html_insertion_mode(const Token& token);
    void apply_rules_for_before_head_insertion_mode(const Token& token);
    void apply_rules_for_in_head_insertion_mode(const Token& token);
    void apply_rules_for_after_head_insertion_mode(const Token& token);
    void apply_rules_for_in_body_insertion_mode(const Token& token);
    void apply_rules_for_after_body_insertion_mode(const Token& token);
    void apply_rules_for_after_after_body_insertion_mode(const Token& token);

    void stop_parsing();
};

}
