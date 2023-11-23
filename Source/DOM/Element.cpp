/*
 * Element.cpp
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

#include "Element.h"

#include "Document.h"
#include "../HTML/Interfaces.h"
#include "../HTML/Semantics/HTMLBodyElement.h"
#include "../HTML/Semantics/HTMLHeadElement.h"
#include "../HTML/Semantics/HTMLHeadingElement.h"
#include "../HTML/Semantics/HTMLHtmlElement.h"
#include "../Infra/Namespaces.h"
#include "../Infra/Strings.h"

#include <cassert>

namespace DOM {

// https://dom.spec.whatwg.org/#concept-element-qualified-name
std::string Element::qualified_name() const
{
    return m_local_name;
}

// https://dom.spec.whatwg.org/#element-html-uppercased-qualified-name
std::string Element::html_uppercased_qualified_name() const
{
    std::string qualified_name { this->qualified_name() };
    if (m_namespace == Infra::Namespace::HTML && m_node_document.is_html_document())
    {
        qualified_name = Infra::ascii_uppercase(qualified_name);
    }
    return qualified_name;
}

const std::string& element_interface_for(const std::string& namespace_, const std::string& local_name)
{
    if (namespace_ == Infra::Namespace::HTML)
    {
        if (local_name == "html")
        {
            return HTML::Interfaces::HTMLHtmlElement;
        }
        if (local_name == "head")
        {
            return HTML::Interfaces::HTMLHeadElement;
        }
        if (local_name == "body")
        {
            return HTML::Interfaces::HTMLBodyElement;
        }
        if (local_name == "h1"
        || local_name == "h2"
        || local_name == "h3"
        || local_name == "h4"
        || local_name == "h5"
        || local_name == "h6")
        {
            return HTML::Interfaces::HTMLHeadingElement;
        }
    }
    abort();
}

Element* create_element(Document& document, const std::string& namespace_, const std::string& local_name)
{
    Element* result { nullptr };
    const std::string& interface { element_interface_for(namespace_, local_name) };
    if (interface == HTML::Interfaces::HTMLHtmlElement)
    {
        result = new HTML::HTMLHtmlElement(document, namespace_, local_name);
    }
    else if (interface == HTML::Interfaces::HTMLHeadElement)
    {
        result = new HTML::HTMLHeadElement(document, namespace_, local_name);
    }
    else if (interface == HTML::Interfaces::HTMLBodyElement)
    {
        result = new HTML::HTMLBodyElement(document, namespace_, local_name);
    }
    else if (interface == HTML::Interfaces::HTMLHeadingElement)
    {
        result = new HTML::HTMLHeadingElement(document, namespace_, local_name);
    }
    assert(result);
    return result;
}

}
