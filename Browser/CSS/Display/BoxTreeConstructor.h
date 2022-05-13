//
//  BoxTreeConstructor.h
//  Browser
//
//  Created by Vitaly Dyachkov on 10.05.22.
//

#pragma once

#include "../../DOM/Node.h"
#include "BoxTree.h"
#include <stack>

namespace CSS {

class BoxTreeConstructor
{
public:
    BoxTree::Node* construct_tree(const DOM::Node* node);
    
private:
    BoxTree::Node* create_node_for(const DOM::Node* node);
    
    std::stack<BoxTree::Node*> m_ancestor_stack;
};

}
