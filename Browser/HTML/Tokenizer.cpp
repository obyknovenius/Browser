//
//  Tokenizer.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#include "Tokenizer.h"

#include <iostream>

namespace HTML {

int lowercase(int character)
{
    return tolower(character);
}

bool is_ascii_alpha(int character)
{
    return isalpha(character);
}

bool is_ascii_upper_alpha(int character)
{
    return isupper(character);
}

int Tokenizer::consume_next_input_character()
{
    if (m_reconsume)
    {
        m_reconsume = false;
        return m_current_input_character;
    }
    
    m_current_input_character = m_next_input_character;
    m_next_input_character = m_input_stream.get();
    
    return m_current_input_character;
}

Token* Tokenizer::next_token()
{
    for(;;)
    {
        switch (m_state)
        {
            case State::Data:
            {
                int current_input_character = consume_next_input_character();
                
                if (current_input_character == '<')
                {
                    switch_to(State::TagOpen);
                    break;
                }
                
                if (current_input_character == EOF)
                {
                    return new EndOfFile {};
                }
                
                return new Character {(char)current_input_character};
            }
                
            case State::TagOpen:
            {
                int current_input_character = consume_next_input_character();
                
                if (current_input_character == '/')
                {
                    switch_to(State::EndTagOpen);
                    break;
                }
                
                if (is_ascii_alpha(current_input_character))
                {
                    create_token<StartTag>();
                    reconsume_in(State::TagName);
                    break;
                }
            }
                
            case State::EndTagOpen:
            {
                int current_input_character = consume_next_input_character();
                
                if (is_ascii_alpha(current_input_character))
                {
                    create_token<EndTag>();
                    reconsume_in(State::TagName);
                    break;
                }
            }
                
            case State::TagName:
            {
                int current_input_character = consume_next_input_character();
                
                if (current_input_character == '\t'
                    || current_input_character == '\n'
                    || current_input_character == '\f'
                    || current_input_character == ' ')
                {
                    switch_to(State::BeforeAttributeName);
                    break;
                }
                
                if (current_input_character == '>')
                {
                    switch_to(State::Data);
                    return current_tag_token();
                }
                
                current_tag_token()->tag_name() += current_input_character;
                break;
            }
                
            case State::BeforeAttributeName:
            {
                consume_next_input_character();
                
                current_tag_token()->start_new_attribute();
                reconsume_in(State::AttributeName);
                break;
            }
                
            case State::AttributeName:
            {
                int current_input_character = consume_next_input_character();
                
                if (current_input_character == '=')
                {
                    switch_to(State::BeforeAttributeValue);
                    break;
                }
                
                if (is_ascii_upper_alpha(current_input_character))
                {
                    current_tag_token()->current_attribute()->name += lowercase(current_input_character);
                    break;
                }
                
                current_tag_token()->current_attribute()->name += current_input_character;
                break;
            }
                
            case State::AfterAttributeName:
            {
                consume_next_input_character();
                
                break;
            }
                
            case State::BeforeAttributeValue:
            {
                consume_next_input_character();
                
                reconsume_in(State::AttributeValueUnquoted);
                break;
            }
                
            case State::AttributeValueDoubleQuoted:
            {
                consume_next_input_character();
                
                break;
            }
                
            case State::AttributeValueSingleQuoted:
            {
                consume_next_input_character();
                
                break;
            }
                
            case State::AttributeValueUnquoted:
            {
                int current_input_character = consume_next_input_character();
                
                if (current_input_character == '>')
                {
                    switch_to(State::Data);
                    return current_tag_token();
                }
                
                current_tag_token()->current_attribute()->value += current_input_character;
                break;
                
            }
                
            case State::AfterAttributeValueQuoted:
            {
                consume_next_input_character();
                
                break;
            }
        }
    }
}

}
