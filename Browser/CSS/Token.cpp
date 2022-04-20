//
//  Token.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 25.03.22.
//

#include "Token.h"
#include <iostream>
#include <cassert>

namespace CSS::Parser {

std::ostream& operator<<(std::ostream& out, const Token& token)
{
    switch (token.m_type)
    {
        case Token::Type::Ident:
        case Token::Type::Delim:
            out << token.m_value;
            break;
        case Token::Type::Whitespace:
            out << ' ';
            break;
        case Token::Type::Colon:
            out << ':';
            break;
        case Token::Type::Semicolon:
            out << ';';
            break;
        case Token::Type::LeftCurlyBracket:
            out << '{';
            break;
        case Token::Type::RightCurlyBracket:
            out << '}';
            break;
        case Token::Type::EOF_:
            out << "EOF";
            break;
        default:
            assert(false);
    }
    return out;
}

}
