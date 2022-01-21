//
//  Parser.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 04.01.22.
//

#include "Parser.h"

namespace HTML {

void Parser::process(Token *token)
{
    switch (m_parse_state.m_insertion_mode)
    {
        case InsertionMode::Initial:
            /*if (Character* character = dynamic_cast<Character*>(token) && *character == ' ') {
            } else if (Comment* comment = dynamic_cast<Comment*>(token)) {
                
            } else if (DOCTYPE* doctype = dynamic_cast<DOCTYPE*>(token)) {
                m_document.append(DocumentType(doctype.name))
            }*/
            break;
            
        default:
            break;
    }
}

}
