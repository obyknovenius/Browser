//
//  Tokenizer.h
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#pragma once

#include "Token.h"
#include <fstream>

namespace CSS {

class Tokenizer final
{
public:
    Tokenizer(std::ifstream& input) : m_input { input } {}
    
    Token consume_token();

private:
    std::ifstream& m_input;
    
    char m_current_input_code_point {};
    
    void consume_next_input_code_point() { m_current_input_code_point = m_input.get(); }
    void reconsume_current_input_code_point() { m_input.unget(); }
            
    bool current_input_code_point_is_eof() { return m_input.eof(); }
    bool current_input_code_point_is_whitespace()
    {
        return m_current_input_code_point == '\n'
            || m_current_input_code_point == '\t'
            || m_current_input_code_point == ' ';
    }
    bool current_input_code_point_is(char code_point) { return m_current_input_code_point == code_point; }
    
    bool next_input_character_is_whitespace()
    {
        int next_input_code_point { m_input.peek() };
        return next_input_code_point == '\n'
            || next_input_code_point == '\t'
            || next_input_code_point == ' ';
    }
    
    void consume_as_much_whitespace_as_possible()
    {
        while (next_input_character_is_whitespace())
        {
            consume_next_input_code_point();
        }
    }
};

}
