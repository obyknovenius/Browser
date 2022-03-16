//
//  Token.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 22.12.21.
//

#include "Token.h"
#include <cassert>

namespace HTML {

bool Token::is_one_of(std::initializer_list<char> characters) const
{
    assert(m_type == Type::Character);
    
    for (char character : characters)
    {
        if (m_data.length() == 1 && m_data[0] == character)
        {
            return true;
        }
    }
    return false;
}

bool Token::tag_name_is_one_of(std::initializer_list<std::string_view> tag_names) const
{
    assert(m_type == Type::StartTag || m_type == Type::EndTag);
    
    for (std::string_view tag_name : tag_names)
    {
        if (m_tag_name == tag_name)
        {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const Token& token)
{
    switch (token.m_type)
    {
        case Token::Type::DOCTYPE:
            out << "<!DOCTYPE " << *token.m_name << ">";
            break;
        case Token::Type::StartTag:
            out << "<" << token.m_tag_name;
            for (const auto& attribute : token.m_attributes)
            {
                out << " " << attribute.name << "=" << attribute.value;
            }
            out << ">";
            break;
        case Token::Type::EndTag:
            out << "</" << token.m_tag_name << ">";
            break;
        case Token::Type::Comment:
            out << "<!--" << token.m_data << "-->";
            break;
        case Token::Type::Character:
            out << token.m_data;
            break;
        case Token::Type::EndOfFile:
            out << "end-of-file";
            break;
        default:
            assert(false);
    }
    return out;
}

}
