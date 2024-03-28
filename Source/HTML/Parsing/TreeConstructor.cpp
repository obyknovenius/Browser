/*
 * TreeConstructor.cpp
 *
 * Copyright 2024 Vitaly Dyachkov <obyknovenius@me.com>
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

#include "TreeConstructor.h"

#include "Token.h"
#include "../Document.h"
#include "../../DOM/Comment.h"
#include "../../DOM/DocumentType.h"
#include "../../DOM/Element.h"
#include "../../DOM/Node.h"
#include "../../Infra/Namespaces.h"

#include <cassert>
#include <iostream>

namespace HTML {

InsertionLocation TreeConstructor::appropriate_place_for_inserting_node()
{
    DOM::Node* target { m_parse_state.current_node() };
    assert(target);
    InsertionLocation adjusted_insertion_location { *target };
    return adjusted_insertion_location;
}

DOM::Element* TreeConstructor::create_element_for(const Token& token, const std::string& namespace_, const DOM::Node& intended_parent)
{
    auto& document { intended_parent.node_document() };
    auto& local_name { token.tag_name() };
    auto* element { create_element(document, local_name, namespace_) };
    return element;
}

void TreeConstructor::insert_element_at_adjusted_insertion_location(DOM::Element& element)
{
    auto adjusted_insertion_location { appropriate_place_for_inserting_node() };
    insert(element, adjusted_insertion_location.inside(), adjusted_insertion_location.before());
}

DOM::Element* TreeConstructor::insert_foreign_element_for(const Token& token, const std::string& namespace_, bool only_add_to_element_stack)
{
    auto adjusted_insertion_location { appropriate_place_for_inserting_node() };
    auto* element { create_element_for(token, namespace_, adjusted_insertion_location.inside()) };
    if (!only_add_to_element_stack)
        insert_element_at_adjusted_insertion_location(*element);
    m_parse_state.stack_of_open_elements.push(element);
    return element;
}

DOM::Element* TreeConstructor::insert_html_element_for(const Token& token)
{
    return insert_foreign_element_for(token, Infra::Namespace::HTML, false);
}

void TreeConstructor::insert_comment(const Token& token, std::optional<InsertionLocation> position)
{
    const auto& data { token.data() };
    auto adjusted_insertion_location { position ? *position : appropriate_place_for_inserting_node() };
    auto* node { new DOM::Comment { adjusted_insertion_location.inside().node_document(), data } };
    insert(*node, adjusted_insertion_location.inside(), adjusted_insertion_location.before());
}

bool TreeConstructor::dispatch(const Token& token)
{
    process_using_rules_for(m_parse_state.insertion_mode, token);

    if (token.is_end_of_file())
        return true;

    std::cout << token;
    return false;
}

void TreeConstructor::process_using_rules_for(InsertionMode insertion_mode, const Token& token)
{
    switch (insertion_mode)
    {
        case InsertionMode::Initial:
            apply_rules_for_initial_insertion_mode(token);
            break;
        case InsertionMode::BeforeHtml:
            apply_rules_for_before_html_insertion_mode(token);
            break;
        case InsertionMode::BeforeHead:
            apply_rules_for_before_head_insertion_mode(token);
            break;
        case InsertionMode::InHead:
            apply_rules_for_in_head_insertion_mode(token);
            break;
        case InsertionMode::AfterHead:
            apply_rules_for_after_head_insertion_mode(token);
            break;
        case InsertionMode::InBody:
            apply_rules_for_in_body_insertion_mode(token);
            break;
        case InsertionMode::AfterBody:
            apply_rules_for_after_body_insertion_mode(token);
            break;
        case InsertionMode::AfterAfterBody:
            apply_rules_for_after_after_body_insertion_mode(token);
            break;
    }
}

void TreeConstructor::apply_rules_for_initial_insertion_mode(const Token& token)
{
    if (token.is_comment())
    {
        insert_comment(token, InsertionLocation { m_document });
        return;
    }

    if (token.is_doctype())
    {
        std::string name { token.name() ? *token.name() : "" };
        auto* document_type { new DOM::DocumentType { m_document, name } };
        append(*document_type, m_document);
        m_parse_state.insertion_mode = InsertionMode::BeforeHtml;
        return;
    }

    m_parse_state.insertion_mode = InsertionMode::BeforeHtml;
    reprocess(token);
}

void TreeConstructor::apply_rules_for_before_html_insertion_mode(const Token& token)
{
    if (token == '\t' || token == '\n' || token == '\f' || token == ' ')
        return;

    if (token.is_start_tag() && token.tag_name() == "html")
    {
        auto* element { create_element_for(token, Infra::Namespace::HTML, m_document) };
        append(*element, m_document);
        m_parse_state.stack_of_open_elements.push(element);
        m_parse_state.insertion_mode = InsertionMode::BeforeHead;
        return;
    }
}

void TreeConstructor::apply_rules_for_before_head_insertion_mode(const Token& token)
{
    if (token == '\t' || token == '\n' || token == '\f' || token == ' ')
        return;

    if (token.is_comment())
    {
        insert_comment(token);
        return;
    }

    if (token.is_start_tag() && token.tag_name() == "head")
    {
        auto* element { insert_html_element_for(token) };
        m_head_element_pointer = element;
        switch_to(InsertionMode::InHead);
        return;
    }
}

void TreeConstructor::apply_rules_for_in_head_insertion_mode(const Token& token)
{
    if (token.is_end_tag() && token.tag_name_is("head"))
    {
        m_stack_of_open_elements.pop();
        switch_to(InsertionMode::AfterHead);
        return;
    }
}

void TreeConstructor::apply_rules_for_after_head_insertion_mode(const Token& token)
{
    if (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    {
        insert_character(token);
        return;
    }

    if (token.is_comment())
    {
        insert_comment(token);
        return;
    }

    if (token.is_start_tag() && token.tag_name_is("body"))
    {
        insert_html_element_for(token);
        m_frameset_ok_flag = FramesetOkFlag::NotOk;
        switch_to(InsertionMode::InBody);
        return;
    }
}

void TreeConstructor::apply_rules_for_in_body_insertion_mode(const Token& token)
{
    if (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    {
        insert_character(token);
        return;
    }

    if (token.is_character())
    {
        insert_character(token);
        m_frameset_ok_flag = FramesetOkFlag::NotOk;
        return;
    }

    if (token.is_end_tag() && token.tag_name_is("body"))
    {
        switch_to(InsertionMode::AfterBody);
        return;
    }

    if (token.is_start_tag() && token.tag_name_is_one_of({"h1", "h2", "h3", "h4", "h5", "h6"}))
    {
        insert_html_element_for(token);
        return;
    }

    if (token.is_end_tag() && token.tag_name_is_one_of({"h1", "h2", "h3", "h4", "h5", "h6"}))
    {
        m_stack_of_open_elements.pop_until([](Element* element)
        {
            return is_html_element(*element) && element->tag_name_is_one_of({"h1", "h2", "h3", "h4", "h5", "h6"});
        });
        return;
    }
}

void TreeConstructor::apply_rules_for_after_body_insertion_mode(const Token& token)
{
    if (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    {
        process_using_rules_for(InsertionMode::InBody, token);
        return;
    }

    if (token.is_comment())
    {
        insert_comment(token, InsertionLocation { m_stack_of_open_elements.topmost()} );
        return;
    }

    if (token.is_end_tag() && token.tag_name_is("body"))
    {
        switch_to(InsertionMode::AfterAfterBody);
    }
}

void TreeConstructor::apply_rules_for_after_after_body_insertion_mode(const Token& token)
{
    if (token.is_comment())
    {
        insert_comment(token, InsertionLocation { &m_document} );
        return;
    }

    if (token.is_doctype()
    || (token.is_character() && token.is_one_of({'\t', '\n', '\f', ' '}))
    || (token.is_start_tag() && token.tag_name_is("html")))
    {
        process_using_rules_for(InsertionMode::InBody, token);
        return;
    }

    if (token.is_end_of_file())
    {
        stop_parsing();
    }
})

}
