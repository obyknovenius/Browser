//
//  Tokenizer.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#include "Tokenizer.h"
#include <iostream>
#include <list>
#include <cstdio>

namespace CSS {

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

void Tokenizer::consume_as_much_whitespace_as_possible()
{
    while (is_whitespace(next_input_code_point()))
    {
        consume_next_input_code_point();
    }
}

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

const Token Tokenizer::consume_ident_like_token()
{
    auto string { consume_ident_sequence() };
    return { Token::Type::Ident, string };
}

const Token Tokenizer::consume_token()
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
    
    return Token { Token::Type::Delim, static_cast<char>(code_point)};
}

const std::list<Token>& Tokenizer::tokenize()
{
    for(;;)
    {
        const Token token = consume_token();
        std::cout << token;
        m_tokens.push_back(token);
        
        if (token.is_eof())
        {
            break;
        }
    }
    return m_tokens;
}

}
