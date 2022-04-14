//
//  Tokenizer.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#include "Tokenizer.h"
#include <iostream>
#include <cstdio>

namespace CSS {

std::string Tokenizer::consume_ident_sequence()
{
    std::string result {};
    
    for(;;)
    {
        auto code_point { consume_next_input_code_point() };
        
        if (is_ident_code_point(code_point))
        {
            result += code_point;
        }
        else
        {
            reconsume_current_input_code_point();
            return result;
        }
    }
}

Token Tokenizer::consume_ident_like_token()
{
    auto string { consume_ident_sequence() };
    return { Token::Type::Ident, string };
}

Token Tokenizer::consume_token()
{
    auto code_point { consume_next_input_code_point() };
    
    if (is_whitespace(code_point))
    {
        consume_as_much_whitespace_as_possible();
        return Token { Token::Type::Whitespace };
    }
    
    if (code_point == ':')
    {
        return Token { Token::Type::Colon };
    }
    
    if (code_point == ';')
    {
        return Token { Token::Type::Semicolon };
    }
    
    if (code_point == '{')
    {
        return Token { Token::Type::LeftCurlyBracket };
    }
    
    if (code_point == '}')
    {
        return Token { Token::Type::RightCurlyBracket };
    }
    
    if (is_ident_start_code_point(code_point))
    {
        reconsume_current_input_code_point();
        return consume_ident_like_token();
    }
    
    if (code_point == EOF)
    {
        return Token { Token::Type::EOF_ };
    }
    
    return Token { Token::Type::Delim, static_cast<char>(m_current_input_code_point)};
}

void Tokenizer::tokenize()
{
    Token token {};
    do
    {
        token = consume_token();
        std::cout << token;
        m_token_stream.push(token);
    }
    while (!token.is_eof());
}

}
