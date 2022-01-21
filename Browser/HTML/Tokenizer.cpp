//
//  Tokenizer.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#include "Tokenizer.h"

#include <iostream>

namespace HTML {

void Tokenizer::consume_next_input_character()
{
    if (m_reconsume)
    {
        m_reconsume = false;
        return;
    }
    m_current_input_character = m_next_input_character;
    m_next_input_character = m_input_stream.get();
}

Token* Tokenizer::next_token()
{
    for(;;)
    {
        if (in(State::Data))
        {
            consume_next_input_character();
            
            if (at('<'))
            {
                switch_to(State::TagOpen);
            }
            else if (at(EOF))
            {
                return new EndOfFile {};
            }
            else
            {
                return new Character {(char)current_input_character()};
            }
        }
        
        if (in(State::TagOpen))
        {
            consume_next_input_character();
            
            if (at('/'))
            {
                switch_to(State::EndTagOpen);
            }
            else if (at_ascii_alpha())
            {
                create_token<StartTag>();
                reconsume_in(State::TagName);
            }
        }
        
        if (in(State::EndTagOpen))
        {
            consume_next_input_character();
            
            if (at_ascii_alpha())
            {
                create_token<EndTag>();
                reconsume_in(State::TagName);
            }
        }
        
        if (in(State::TagName))
        {
            consume_next_input_character();
            
            if (at('\t') || at('\n') || at('\f') || at(' '))
            {
                switch_to(State::BeforeAttributeName);
            }
            else if (at('>'))
            {
                switch_to(State::Data);
                return current_tag_token();
            }
            else
            {
                current_tag_token()->tag_name() += current_input_character();
            }
        }
        
        if (in(State::BeforeAttributeName))
        {
            consume_next_input_character();
            current_tag_token()->start_new_attribute();
            reconsume_in(State::AttributeName);
        }
        
        if (in(State::AttributeName))
        {
            consume_next_input_character();
            
            if (at('='))
            {
                switch_to(State::BeforeAttributeValue);
            }
            else if (at_ascii_upper_alpha())
            {
                current_tag_token()->current_attribute()->name += lowercase_current_input_character();
            }
            else
            {
                current_tag_token()->current_attribute()->name += current_input_character();
            }
        }
        
        if (in(State::AfterAttributeName))
        {
            consume_next_input_character();
        }

        if (in(State::BeforeAttributeValue))
        {
            consume_next_input_character();
            reconsume_in(State::AttributeValueUnquoted);
        }

        if (in(State::AttributeValueDoubleQuoted))
        {
            consume_next_input_character();
        }

        if (in(State::AttributeValueSingleQuoted))
        {
            consume_next_input_character();
        }

        if (in(State::AttributeValueUnquoted))
        {
            consume_next_input_character();
            
            if (at('>'))
            {
                switch_to(State::Data);
                return current_tag_token();
            }
            else
            {
                current_tag_token()->current_attribute()->value += current_input_character();
            }
        }

        if (in(State::AfterAttributeValueQuoted))
        {
            consume_next_input_character();
        }
    }
}

}
