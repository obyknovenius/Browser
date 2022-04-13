//
//  Tokenizer.h
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#pragma once

#include "Token.h"
#include "TokenStream.h"
#include <fstream>

namespace CSS {

class Tokenizer final
{
public:
    Tokenizer(std::ifstream& input) : m_input { input } {}
    
    TokenStream& token_stream() { return m_token_stream; }
    
    void tokenize();

private:
    std::ifstream& m_input;
    
    TokenStream m_token_stream {};
    
    int m_current_input_code_point {};
    
    int next_input_code_point() { return m_input.peek(); }
    
    int consume_next_input_code_point() { return m_current_input_code_point = m_input.get(); }
    void reconsume_current_input_code_point() { m_input.putback(m_current_input_code_point); }
    
    bool is_digit(int code_point)
    {
        return code_point >= '0' && code_point <= '9';
    }
    
    bool is_uppercase_letter(int code_point)
    {
        return code_point >= 'A' && code_point <= 'Z';
    }
    
    bool is_lowecase_letter(int code_point)
    {
        return code_point >= 'a' && code_point <= 'z';
    }
    
    bool is_letter(int code_point)
    {
        return is_uppercase_letter(code_point) || is_lowecase_letter(code_point);
    }
    
    bool is_non_ascii_code_point(int code_point)
    {
        return code_point >= 0x0080;
    }
    
    bool is_ident_start_code_point(int code_point)
    {
        return is_letter(code_point)
        || is_non_ascii_code_point(code_point)
        || code_point == '_';
    }
    
    bool is_ident_code_point(int code_point)
    {
        return is_ident_start_code_point(code_point)
        || is_digit(code_point)
        || code_point == '-';
    }
    
    bool is_whitespace(int code_point)
    {
        return code_point == '\n'
        || code_point == '\t'
        || code_point == ' ';
    }
    
    void consume_as_much_whitespace_as_possible()
    {
        while (is_whitespace(next_input_code_point()))
        {
            consume_next_input_code_point();
        }
    }
    
    std::string consume_ident_sequence();
    
    Token consume_ident_like_token();
    
    Token consume_token();
};

}
