//
//  Tokenizer.h
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#pragma once

#include "Token.h"
#include <fstream>
#include <list>

namespace CSS {

class Tokenizer final
{
public:
    Tokenizer(std::ifstream& input) : m_input { input } {}
    
    const std::list<Token>& tokenize();

private:
    std::ifstream& m_input;
    
    std::list<Token> m_tokens {};
            
    int next_input_code_point() { return m_input.peek(); }
    
    int consume_next_input_code_point() { return m_input.get(); }
    void reconsume_current_input_code_point() { m_input.unget(); }
    
    void consume_as_much_whitespace_as_possible();
    
    std::string consume_ident_sequence();
    
    const Token consume_ident_like_token();
    
    const Token consume_token();
};

}
