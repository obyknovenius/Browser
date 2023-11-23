/*
 * TreeConstructor.cpp
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

#include "TreeConstructor.h"

#include "../../DOM/Comment.h"
#include "../../DOM/DocumentType.h"
#include "../../DOM/Element.h"
#include "../../DOM/Node.h"
#include "../../DOM/Text.h"
#include "../../Infra/Namespaces.h"
#include "Token.h"
#include <cassert>

namespace HTML {

// https://html.spec.whatwg.org/multipage/parsing.html#appropriate-place-for-inserting-a-node
InsertionLocation TreeConstructor::appropriate_place_for_inserting_node()
{
    DOM::Node* target { current_node() };
    InsertionLocation adjusted_insertion_location { target };
    return adjusted_insertion_location;
}

static DOM::Node* immediately_before(InsertionLocation insertion_location)
{
    if (insertion_location.before)
    {
        return insertion_location.before->previous_sibling();
    }
    return insertion_location.inside->last_child();
}

static void insert_at(InsertionLocation insertion_location, DOM::Node* node)
{
    insert(node, insertion_location.inside, insertion_location.before);
}

// https://html.spec.whatwg.org/multipage/parsing.html#insert-a-character
void TreeConstructor::insert_character(const CharacterToken& token)
{
    std::string data { token.data() };
    InsertionLocation adjusted_insertion_location { appropriate_place_for_inserting_node() };
    if (dynamic_cast<const DOM::Document*>(adjusted_insertion_location.inside))
    {
        return;
    }

    if (auto* node { dynamic_cast<DOM::Text*>(immediately_before(adjusted_insertion_location)) })
    {
        node->data() += data;
    }
    else
    {
        node = new DOM::Text { adjusted_insertion_location.inside->node_document(), data };
        insert_at(adjusted_insertion_location, node);
    }
}

// https://html.spec.whatwg.org/multipage/parsing.html#insert-a-comment
void TreeConstructor::insert_comment(const CommentToken& token, std::optional<InsertionLocation> position)
{
    const std::string& data { token.data() };
    InsertionLocation adjusted_insertion_location { position ? *position : appropriate_place_for_inserting_node() };
    DOM::Comment* node { new DOM::Comment { m_document, data } };
    insert_at(adjusted_insertion_location, node);
}

// https://html.spec.whatwg.org/multipage/parsing.html#create-an-element-for-the-token
DOM::Element* TreeConstructor::create_element_for(const TagToken& token, const std::string& namespace_, DOM::Node* intended_parent)
{
    DOM::Document& document { intended_parent->node_document() };
    const std::string& local_name { token.name() };
    DOM::Element* element { DOM::create_element(document, namespace_, local_name) };
    return element;
}

// https://html.spec.whatwg.org/multipage/parsing.html#insert-a-foreign-element
DOM::Element* TreeConstructor::insert_foreign_element_for(const TagToken& token, const std::string& namespace_)
{
    InsertionLocation adjusted_insertion_location { appropriate_place_for_inserting_node() };
    DOM::Element* element { create_element_for(token, namespace_, adjusted_insertion_location.inside) };
    insert_at(adjusted_insertion_location, element);
    m_stack_of_open_elements.push(element);
    return element;
}

// https://html.spec.whatwg.org/multipage/parsing.html#insert-an-html-element
DOM::Element* TreeConstructor::insert_html_element_for(const TagToken& token)
{
    return insert_foreign_element_for(token, Infra::Namespace::HTML);
}

void TreeConstructor::dispatch(const Token& next_token)
{
    std::cout << next_token;

    process_using_rules_for(m_insertion_mode, next_token);
}

void TreeConstructor::process_using_rules_for(InsertionMode insertion_mode, const Token& token)
{
    switch (insertion_mode)
    {
        case InsertionMode::Initial:
        {
            apply_rules_for_initial_insertion_mode(token);
            break;
        }
        case InsertionMode::BeforeHtml:
        {
            apply_rules_for_before_html_insertion_mode(token);
            break;
        }
        case InsertionMode::BeforeHead:
        {
            apply_rules_for_before_head_insertion_mode(token);
            break;
        }
        case InsertionMode::InHead:
        {
            apply_rules_for_in_head_insertion_mode(token);
            break;
        }
        case InsertionMode::AfterHead:
        {
            apply_rules_for_after_head_insertion_mode(token);
            break;
        }
        case InsertionMode::InBody:
        {
            apply_rules_for_in_body_insertion_mode(token);
            break;
        }
        case InsertionMode::AfterBody:
        {
            apply_rules_for_after_body_insertion_mode(token);
            break;
        }
        case InsertionMode::AfterAfterBody:
        {
            apply_rules_for_after_after_body_insertion_mode(token);
            break;
        }
    }
}

// https://html.spec.whatwg.org/multipage/parsing.html#the-initial-insertion-mode
void TreeConstructor::apply_rules_for_initial_insertion_mode(const Token& token)
{
    if (const auto* comment_token { dynamic_cast<const CommentToken*>(&token) })
    {
        insert_comment(*comment_token, InsertionLocation { &m_document });
        return;
    }

    if (const auto* doctype_token { dynamic_cast<const DoctypeToken*>(&token) })
    {
        DOM::DocumentType* document_type { new DOM::DocumentType { m_document, *doctype_token->name() } };
        append(document_type, &m_document);
        switch_to(InsertionMode::BeforeHtml);
        return;
    }

    switch_to(InsertionMode::BeforeHtml);
    reprocess(token);
}

// https://html.spec.whatwg.org/multipage/parsing.html#the-before-html-insertion-mode
void TreeConstructor::apply_rules_for_before_html_insertion_mode(const Token& token)
{
    if (const auto* character_token { dynamic_cast<const CharacterToken*>(&token) }; character_token
    && (*character_token == '\t' || *character_token == '\n' || *character_token == '\f' || *character_token == ' '))
    {
        return;
    }

    if (const auto* start_tag { dynamic_cast<const StartTagToken*>(&token) }; start_tag
    && start_tag->name() == "html")
    {
        DOM::Element* element { create_element_for(*start_tag, Infra::Namespace::HTML, &m_document) };
        append(element, &m_document);
        m_stack_of_open_elements.push(element);
        switch_to(InsertionMode::BeforeHead);
        return;
    }
}

// https://html.spec.whatwg.org/multipage/parsing.html#the-before-head-insertion-mode
void TreeConstructor::apply_rules_for_before_head_insertion_mode(const Token& token)
{
    if (const auto* character_token { dynamic_cast<const CharacterToken*>(&token) }; character_token
    && (*character_token == '\t' || *character_token == '\n' || *character_token == '\f' || *character_token == ' '))
    {
        return;
    }

    if (const auto* comment_token { dynamic_cast<const CommentToken*>(&token) })
    {
        insert_comment(*comment_token);
        return;
    }

    if (const auto* start_tag { dynamic_cast<const StartTagToken*>(&token) }; start_tag
    && start_tag->name() == "head")
    {
        DOM::Element* element = insert_html_element_for(*start_tag);
        m_head_element_pointer = element;
        switch_to(InsertionMode::InHead);
        return;
    }
}

// https://html.spec.whatwg.org/multipage/parsing.html#parsing-main-inhead
void TreeConstructor::apply_rules_for_in_head_insertion_mode(const Token& token)
{
    if (const auto* end_tag { dynamic_cast<const EndTagToken*>(&token) }; end_tag
    && end_tag->name() == "head")
    {
        assert(dynamic_cast<HTML::HTMLHeadElement*>(m_stack_of_open_elements.top()));
        m_stack_of_open_elements.pop();
        switch_to(InsertionMode::AfterHead);
        return;
    }
}

// https://html.spec.whatwg.org/multipage/parsing.html#the-after-head-insertion-mode
void TreeConstructor::apply_rules_for_after_head_insertion_mode(const Token& token)
{
    if (const auto* character_token { dynamic_cast<const CharacterToken*>(&token) }; character_token
    && (*character_token == '\t' || *character_token == '\n' || *character_token == '\f' || *character_token == ' '))
    {
        insert_character(*character_token);
        return;
    }
}

// https://html.spec.whatwg.org/multipage/parsing.html#parsing-main-inbody
void TreeConstructor::apply_rules_for_in_body_insertion_mode(const Token& token)
{
    if (const auto* character_token { dynamic_cast<const CharacterToken*>(&token) }; character_token
    && (*character_token == '\t' || *character_token == '\n' || *character_token == '\f' || *character_token == ' '))
    {
        insert_character(*character_token);
        return;
    }

    if (const auto* character_token { dynamic_cast<const CharacterToken*>(&token) })
    {
        insert_character(*character_token);
        m_frameset_ok_flag = FramesetOkFlag::NotOk;
        return;
    }

    if (const auto* comment_token { dynamic_cast<const CommentToken*>(&token) })
    {
        insert_comment(*comment_token, InsertionLocation { &m_document });
        return;
    }

    if (const auto* end_tag { dynamic_cast<const EndTagToken*>(&token) })
    {
        if (end_tag->name() == "body")
        {
            switch_to(InsertionMode::AfterBody);
            return;
        }
    }
}

// https://html.spec.whatwg.org/multipage/parsing.html#parsing-main-afterbody
void TreeConstructor::apply_rules_for_after_body_insertion_mode(const Token& token)
{
    if (const auto* character_token { dynamic_cast<const CharacterToken*>(&token) }; character_token
    && (*character_token == '\t' || *character_token == '\n' || *character_token == '\f' || *character_token == ' '))
    {
        process_using_rules_for(InsertionMode::InBody, token);
        return;
    }

    if (const auto* comment_token { dynamic_cast<const CommentToken*>(&token) })
    {
        assert(dynamic_cast<HTML::HTMLHeadElement*>(m_stack_of_open_elements.top()));
        insert_comment(*comment_token, InsertionLocation { m_stack_of_open_elements.top(), nullptr });
        return;
    }

    if (const auto* start_tag { dynamic_cast<const StartTagToken*>(&token) }; start_tag
    && start_tag->name() == "html")
    {
        process_using_rules_for(InsertionMode::InBody, token);
        return;
    }

    if (const auto* end_tag { dynamic_cast<const EndTagToken*>(&token) }; end_tag
    && end_tag->name() == "html")
    {
        switch_to(InsertionMode::AfterAfterBody);
        return;
    }

    if (const auto* eof_token { dynamic_cast<const EndOfFileToken*>(&token) })
    {
        stop_parsing();
    }
}

void TreeConstructor::apply_rules_for_after_after_body_insertion_mode(const Token& token)
{
    if (const auto* comment_token { dynamic_cast<const CommentToken*>(&token) })
    {
        assert(dynamic_cast<HTML::HTMLHeadElement*>(m_stack_of_open_elements.top()));
        insert_comment(*comment_token, InsertionLocation { &m_document, nullptr });
        return;
    }

    if (const auto* eof_token { dynamic_cast<const EndOfFileToken*>(&token) })
    {
        stop_parsing();
    }
}

// https://html.spec.whatwg.org/multipage/parsing.html#stop-parsing
void TreeConstructor::stop_parsing()
{
    while (!m_stack_of_open_elements.empty())
    {
        m_stack_of_open_elements.pop();
    }
}

}
