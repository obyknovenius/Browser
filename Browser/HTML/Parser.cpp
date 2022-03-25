//
//  Parser.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 04.01.22.
//

#include "Tokenizer.h"
#include "TreeConstruction.h"
#include "Parser.h"
#include <iostream>

namespace HTML {

Document* Parser::parse()
{
    do
    {
        m_tokenizer.resume();
    }
    while (!m_tree_construction.construct_tree());
    
    return m_document;
}

}
