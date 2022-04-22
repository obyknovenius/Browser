//
//  Tokenizer.h
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#pragma once

#include "Token.h"
#include "TokenStream.h"
#include "List.h"
#include <fstream>

namespace CSS {

class Tokenizer final
{
public:
    Tokenizer(std::ifstream& input) : m_input { input } {}
    
    TokenStream<Token> tokenize();

private:
    std::ifstream& m_input;
    
    List<Token> m_tokens {};
            
    int next_input_code_point() { return m_input.peek(); }
    
    int consume_next_input_code_point() { return m_input.get(); }
    void reconsume_current_input_code_point() { m_input.unget(); }
    
    void consume_as_much_whitespace_as_possible();
    
    std::string consume_ident_sequence();
    
    const Token consume_ident_like_token();
    
    const Token consume_token();
};

}
