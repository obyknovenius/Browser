//
//  Token.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 22.12.21.
//

#include "Token.h"

namespace HTML {

std::ostream& operator<<(std::ostream& out, const DOCTYPE& doctype)
{
    return out << "DOCTYPE";
}

std::ostream& operator<<(std::ostream& out, const StartTag& start_tag)
{
    out << "<" << start_tag.m_tag_name;
    for (const auto& attribute : start_tag.m_attributes)
    {
        out << " " << attribute.name << "=" << attribute.value;
    }
    return out << ">";
}

std::ostream& operator<<(std::ostream& out, const EndTag& end_tag)
{
    return out << "</" << end_tag.m_tag_name << ">";
}

std::ostream& operator<<(std::ostream& out, const Comment& comment)
{
    return out << "//" << comment.m_data;
}

std::ostream& operator<<(std::ostream& out, const Character& character)
{
    return out << character.m_data;
}

std::ostream& operator<<(std::ostream& out, const EndOfFile& end_of_file)
{
    return out << "end-of-file";
}

}
