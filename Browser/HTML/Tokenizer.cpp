//
//  Tokenizer.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#include "Tokenizer.h"

namespace HTML {

int lowercase(int character)
{
    return tolower(character);
}

bool Tokenizer::next_few_characters_are(std::string_view characters)
{
    std::streampos pos = m_input_stream.tellg();
    for (char character : characters) {
        if (character != m_input_stream.get()) {
            m_input_stream.seekg(pos);
            return false;
        }
    }
    m_number_of_characters_to_consume = characters.length();
    m_input_stream.seekg(pos);
    return true;
}

bool Tokenizer::next_few_characters_are_ascii_case_insensitive(const std::string_view characters)
{
    std::streampos pos = m_input_stream.tellg();
    for (char character : characters) {
        if (tolower(character) != tolower(m_input_stream.get())) {
            m_input_stream.seekg(pos);
            return false;
        }
    }
    m_number_of_characters_to_consume = characters.length();
    m_input_stream.seekg(pos);
    return true;
}


void Tokenizer::consume_those_characters()
{
    for (int i { 0 }; i < m_number_of_characters_to_consume; ++i) {
        consume_next_input_character();
    }
    m_number_of_characters_to_consume = 0;
}

void Tokenizer::operator>>(Token** token)
{
    for(;;)
    {
        switch (m_state)
        {
            case State::Data:
            {
                consume_next_input_character();
                
                if (current_input_character_is('<'))
                {
                    switch_to(State::TagOpen);
                    break;
                }
                
                if (current_input_character_is(EOF))
                {
                    *token = new EndOfFile {};
                    return;
                }
                
                *token = new Character { static_cast<char>(current_input_character()) };
                return;
            }
                
            case State::TagOpen:
            {
                consume_next_input_character();
                
                if (current_input_character_is('!'))
                {
                    switch_to(State::MarkupDeclarationOpen);
                    break;
                }
                
                if (current_input_character_is('/'))
                {
                    switch_to(State::EndTagOpen);
                    break;
                }
                
                if (current_input_character_is_ascii_alpha())
                {
                    create_token<StartTag>();
                    reconsume_in(State::TagName);
                    break;
                }
            }
                
            case State::EndTagOpen:
            {
                consume_next_input_character();
                
                if (current_input_character_is_ascii_alpha())
                {
                    create_token<EndTag>();
                    reconsume_in(State::TagName);
                    break;
                }
            }
                
            case State::TagName:
            {
                consume_next_input_character();
                
                if (current_input_character_is('\t')
                    || current_input_character_is('\n')
                    || current_input_character_is('\f')
                    || current_input_character_is(' '))
                {
                    switch_to(State::BeforeAttributeName);
                    break;
                }
                
                if (current_input_character_is('>'))
                {
                    switch_to(State::Data);
                    *token = current_token<Tag*>();
                    return;
                }
                
                current_token<Tag*>()->tag_name() += current_input_character();
                break;
            }
                
            case State::BeforeAttributeName:
            {
                consume_next_input_character();
                current_token<Tag*>()->start_new_attribute();
                reconsume_in(State::AttributeName);
                break;
            }
                
            case State::AttributeName:
            {
                consume_next_input_character();
                
                if (current_input_character_is('='))
                {
                    switch_to(State::BeforeAttributeValue);
                    break;
                }
                
                if (current_input_character_is_ascii_upper_alpha())
                {
                    current_token<Tag*>()->current_attribute()->name += lowercase(current_input_character());
                    break;
                }
                
                current_token<Tag*>()->current_attribute()->name += current_input_character();
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
                consume_next_input_character();
                
                if (current_input_character_is('>'))
                {
                    switch_to(State::Data);
                    *token = current_token<Tag*>();
                    return;
                }
                
                current_token<Tag*>()->current_attribute()->value += current_input_character();
                break;
                
            }
                
            case State::AfterAttributeValueQuoted:
            {
                consume_next_input_character();
                
                break;
            }
                
            case State::MarkupDeclarationOpen:
            {
                if (next_few_characters_are("--"))
                {
                    consume_those_characters();
                    create_token<Comment>("");
                    switch_to(State::CommentStart);
                    break;
                }
                
                if (next_few_characters_are_ascii_case_insensitive("DOCTYPE"))
                {
                    consume_those_characters();
                    switch_to(State::Doctype);
                    break;
                }
            }
                
            case State::CommentStart:
            {
                consume_next_input_character();
                
                if (current_input_character_is('-'))
                {
                    switch_to(State::CommentStartDash);
                    break;
                }
                
                reconsume_in(State::Comment);
                break;
            }
                
            case State::CommentStartDash:
            {
                consume_next_input_character();
                
                if (current_input_character_is('-'))
                {
                    switch_to(State::CommentEnd);
                    break;
                }
            }
                
            case State::Comment:
            {
                consume_next_input_character();
                
                if (current_input_character_is('-'))
                {
                    switch_to(State::CommentEndDash);
                    break;
                }
                
                current_token<Comment*>()->data() += current_input_character();
                break;
            }
                
            case State::CommentEndDash:
            {
                consume_next_input_character();
                
                if (current_input_character_is('-'))
                {
                    switch_to(State::CommentEnd);
                    break;
                }
            }
                
            case State::CommentEnd:
            {
                consume_next_input_character();
                
                if (current_input_character_is('>'))
                {
                    switch_to(State::Data);
                    *token = current_token<Comment*>();
                    return;
                }
            }
                
            case State::CommentEndBang:
            {
                consume_next_input_character();
                
                reconsume_in(State::Comment);
                break;
            }
                
            case State::Doctype:
            {
                consume_next_input_character();
                
                if (current_input_character_is('\t')
                    || current_input_character_is('\n')
                    || current_input_character_is('\f')
                    || current_input_character_is(' '))
                {
                    switch_to(State::BeforeDoctypeName);
                    break;
                }
                
                if (current_input_character_is('>'))
                {
                    reconsume_in(State::BeforeDoctypeName);
                    break;
                }
            }
                
            case State::BeforeDoctypeName:
            {
                consume_next_input_character();
                
                if (current_input_character_is('\t')
                    || current_input_character_is('\n')
                    || current_input_character_is('\f')
                    || current_input_character_is(' '))
                {
                    break;
                }
                
                if (current_input_character_is_ascii_alpha())
                {
                    create_token<Doctype>(static_cast<char>(lowercase(current_input_character())));
                    switch_to(State::DoctypeName);
                    break;
                }
            }
                
            case State::DoctypeName:
            {
                consume_next_input_character();
                
                if (current_input_character_is('\t')
                    || current_input_character_is('\n')
                    || current_input_character_is('\f')
                    || current_input_character_is(' '))
                {
                    switch_to(State::AfterDoctypeName);
                    break;
                }
                
                if (current_input_character_is('>')) {
                    switch_to(State::Data);
                    *token = current_token<Doctype*>();
                    return;
                }
                
                *current_token<Doctype*>()->name() += current_input_character();
                break;
            }
        }
    }
}

}
