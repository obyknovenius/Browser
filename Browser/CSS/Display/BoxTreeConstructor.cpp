//
//  BoxTreeConstructor.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 10.05.22.
//

#include "BoxTreeConstructor.h"
#include "../../DOM/Document.h"
#include "../../DOM/Element.h"
#include "../../DOM/Text.h"
#include "BlockBox.h"
#include "TextRun.h"

namespace CSS {

BoxTree::Node* BoxTreeConstructor::construct_tree(const DOM::Node* dom_node)
{
    BoxTree::Node* box_tree_node { create_node_for(dom_node) };
    
    if (!box_tree_node)
    {
        return {};
    }
    
    if (!m_ancestor_stack.empty())
    {
        box_tree_node->set_parent(m_ancestor_stack.top());
    }
    
    m_ancestor_stack.push(box_tree_node);
    for (const DOM::Node* child { dom_node->first_child() }; child; child = child->next_sibling())
    {
        construct_tree(child);
    }
    m_ancestor_stack.pop();
    
    return box_tree_node;
}

BoxTree::Node* BoxTreeConstructor::create_node_for(const DOM::Node* node)
{
    if (node->is<DOM::Document>())
    {
        return new BlockBox();
    }
    
    if (node->is<DOM::Element>())
    {
        return new BlockBox();
    }
    
    if (const auto* text { node->is<DOM::Text>() })
    {
        return new TextRun(text->data());
    }
    
    return {};
}

}
