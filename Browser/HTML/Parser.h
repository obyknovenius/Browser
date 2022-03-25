//
//  Parser.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 04.01.22.
//

#pragma once

#include "Parser/Tokenizer.h"
#include "Parser/TreeConstruction.h"
#include "../DOM/Document.h"
#include <fstream>

using namespace DOM;

namespace HTML {

class Parser final
{
public:
    Parser(std::ifstream& input_stream)
        : m_tokenizer { input_stream }
        , m_tree_construction { *m_document, m_tokenizer.tokens() }
    {}
    
    Document* parse();
    
private:
    Document* m_document { new Document() };
    
    Tokenizer m_tokenizer;
    TreeConstruction m_tree_construction;
};

}
