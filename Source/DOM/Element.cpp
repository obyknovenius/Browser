/*
 * Element.cpp
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

#include "Element.h"

#include "../HTML/HTMLHeadElement.h"
#include "../HTML/HTMLHtmlElement.h"

namespace DOM {

namespace Interface {

const std::string Element { "Element" };

}

static const std::string& element_interface_for(const std::string& name, const std::string& namespace_)
{
    if (namespace_ == Infra::Namespace::HTML)
    {
        if (name == "head")
        {
            return HTML::Interface::HTMLHeadElement;
        }
        if (name == "html")
        {
            return HTML::Interface::HTMLHtmlElement;
        }
    }
    return Interface::Element;
}

Element* create_element(const Document& document, const std::string& local_name, const std::string& namespace_)
{
    Element* result {};
    const std::string& interface { element_interface_for(local_name, namespace_) };

    if (interface == HTML::Interface::HTMLHeadElement)
    {
        return new HTML::HTMLHeadElement(document, namespace_, local_name);
    }

    if (interface == HTML::Interface::HTMLHtmlElement)
    {
        return new HTML::HTMLHtmlElement(document, namespace_, local_name);
    }

    if (interface == Interface::Element)
    {
        return new Element(document, namespace_, local_name);
    }

    assert(false);
    return {};
}

}
