//
//  Tree.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 13.05.22.
//

#include "Tree.h"

namespace DOM {

void dump_tree(const Node* root, int level)
{
    for (int i {0}; i < level; ++i)
    {
        std::cout << ' ';
    }
    
    std::cout << *root << '\n';
        
    for (const Node* node { root->first_child() }; node; node = node->next_sibling())
    {
        dump_tree(node, level + 1);
    }
}

}
