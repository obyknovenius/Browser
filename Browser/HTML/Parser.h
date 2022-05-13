//
//  Parser.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 04.01.22.
//

#pragma once

#include "Tokenizer.h"
#include "TreeConstructor.h"
#include "../DOM/Document.h"
#include <fstream>

using namespace DOM;

namespace HTML {

class Parser final
{
public:
    Parser(std::ifstream& input_stream)
        : m_tokenizer { input_stream }
        , m_tree_constructor { *m_document, m_tokenizer.tokens() }
    {}
    
    Document* parse();
    
private:
    Document* m_document { new Document() };
    
    Tokenizer m_tokenizer;
    TreeConstructor m_tree_constructor;
};

}
