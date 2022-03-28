//
//  Tokenizer.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#include "Tokenizer.h"

namespace CSS {

Token Tokenizer::consume_token()
{
    consume_next_input_code_point();
    
    if (current_input_code_point_is_whitespace())
    {
        consume_as_much_whitespace_as_possible();
        return Token { Token::Type::Whitespace };
    }
    
    if (current_input_code_point_is(':'))
    {
        return Token { Token::Type::Colon };
    }
    
    if (current_input_code_point_is(';'))
    {
        return Token { Token::Type::Semicolon };
    }
    
    if (current_input_code_point_is('{'))
    {
        return Token { Token::Type::LeftCurlyBracket };
    }
    
    if (current_input_code_point_is('}'))
    {
        return Token { Token::Type::RightCurlyBracket };
    }
    
    if (current_input_code_point_is_eof())
    {
        return Token { Token::Type::EOF_ };
    }
    
    return Token { Token::Type::Delim, m_current_input_code_point };
}

}
