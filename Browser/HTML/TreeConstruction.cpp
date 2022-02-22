//
//  TreeConstruction.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#include "TreeConstruction.h"

namespace HTML {

bool TreeConstruction::dispatch(Token* token)
{
    if (auto* doctype = token->as<HTML::DOCTYPE*>())
    {
        std::cout << *doctype;
    }
    
    if (auto* start_tag = token->as<HTML::StartTag*>())
    {
        std::cout << *start_tag;
    }
    
    if (auto* end_tag = token->as<HTML::EndTag*>())
    {
        std::cout << *end_tag;
    }
    
    if (auto* comment = token->as<HTML::Comment*>())
    {
        std::cout << *comment;
    }
    
    if (auto* character = token->as<HTML::Character*>())
    {
        std::cout << *character;
    }
    
    if (auto* end_of_file = token->as<HTML::EndOfFile*>())
    {
        std::cout << *end_of_file;
        return true;
    }
    
    return false;
}

}
