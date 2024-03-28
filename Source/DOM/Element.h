/*
 * Element.h
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

#pragma once

#include "Document.h"
#include "Node.h"
#include "../Infra/Namespaces.h"
#include "../Infra/Strings.h"
#include <format>
#include <optional>
#include <string>

namespace DOM {

class Document;

class Element : public Node
{
public:
    Element(const Document& node_document) : Node { node_document } {}

    const std::string& namespace_() const { return m_namespace_; }

    std::string qualified_name() const
    {
        if (!m_namespace_prefix)
            return m_local_name;
        return std::format("{}:{}", *m_namespace_prefix, m_local_name);
    }

    std::string html_uppercased_qualified_name() const
    {
        auto qualified_name = this->qualified_name();
        if (m_namespace_ == Infra::Namespace::HTML && node_document().is_html_document())
            qualified_name = Infra::ascii_uppercase(qualified_name);
        return qualified_name;
    }

    std::string tag_name() const { return html_uppercased_qualified_name(); }

private:
    std::string m_namespace_;
    std::optional<std::string> m_namespace_prefix;
    std::string m_local_name;
};

Element* create_element(const Document& document, const std::string& local_name, const std::string& namespace_);

}
