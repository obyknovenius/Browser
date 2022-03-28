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
    for (char character : characters)
    {
        if (character != m_input_stream.get())
        {
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
    for (char character : characters)
    {
        if (tolower(character) != tolower(m_input_stream.get()))
        {
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
    for (int i { 0 }; i < m_number_of_characters_to_consume; ++i)
    {
        consume_next_input_character();
    }
    m_number_of_characters_to_consume = 0;
}

void Tokenizer::resume()
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
                }
                else if (current_input_character_is_eof())
                {
                    emit_end_of_file_token();
                    return;
                }
                else
                {
                    emit_current_input_character_as_character_token();
                    return;
                }
                break;
            }
            case State::TagOpen:
            {
                consume_next_input_character();
                
                if (current_input_character_is('!'))
                {
                    switch_to(State::MarkupDeclarationOpen);
                }
                else if (current_input_character_is('/'))
                {
                    switch_to(State::EndTagOpen);
                }
                else if (current_input_character_is_ascii_alpha())
                {
                    auto& start_tag { create_start_tag_token() };
                    start_tag.m_tag_name = "";
                    reconsume_in(State::TagName);
                }
                break;
            }
            case State::EndTagOpen:
            {
                consume_next_input_character();
                
                if (current_input_character_is_ascii_alpha())
                {
                    auto& end_tag { create_end_tag_token() };
                    end_tag.m_tag_name = "";
                    reconsume_in(State::TagName);
                }
                break;
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
                }
                else if (current_input_character_is('>'))
                {
                    switch_to(State::Data);
                    emit_current_token();
                    return;
                }
                else
                {
                    current_tag_token().m_tag_name += m_current_input_character;
                }
                break;
            }
            case State::BeforeAttributeName:
            {
                consume_next_input_character();
                current_tag_token().start_new_attribute();
                reconsume_in(State::AttributeName);
                break;
            }
            case State::AttributeName:
            {
                consume_next_input_character();
                
                if (current_input_character_is('='))
                {
                    switch_to(State::BeforeAttributeValue);
                }
                else if (current_input_character_is_ascii_upper_alpha())
                {
                    current_tag_token().current_attribute().name += lowercase(m_current_input_character);
                }
                else
                {
                    current_tag_token().current_attribute().name += m_current_input_character;
                }
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
                    emit_current_token();
                    return;
                }
                else
                {
                    current_tag_token().current_attribute().value += m_current_input_character;
                }
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
                    create_comment_token("");
                    switch_to(State::CommentStart);
                }
                else if (next_few_characters_are_ascii_case_insensitive("DOCTYPE"))
                {
                    consume_those_characters();
                    switch_to(State::Doctype);
                }
                break;
            }
            case State::CommentStart:
            {
                consume_next_input_character();
                
                if (current_input_character_is('-'))
                {
                    switch_to(State::CommentStartDash);
                }
                else
                {
                    reconsume_in(State::Comment);
                }
                break;
            }
            case State::CommentStartDash:
            {
                consume_next_input_character();
                
                if (current_input_character_is('-'))
                {
                    switch_to(State::CommentEnd);
                }
                break;
            }
            case State::Comment:
            {
                consume_next_input_character();
                
                if (current_input_character_is('-'))
                {
                    switch_to(State::CommentEndDash);
                }
                else
                {
                    current_comment_token().m_data += m_current_input_character;
                }
                break;
            }
            case State::CommentEndDash:
            {
                consume_next_input_character();
                
                if (current_input_character_is('-'))
                {
                    switch_to(State::CommentEnd);
                }
                break;
            }
            case State::CommentEnd:
            {
                consume_next_input_character();
                
                if (current_input_character_is('>'))
                {
                    switch_to(State::Data);
                    emit_current_token();
                    return;
                }
                break;
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
                }
                else if (current_input_character_is('>'))
                {
                    reconsume_in(State::BeforeDoctypeName);
                }
                break;
            }
            case State::BeforeDoctypeName:
            {
                consume_next_input_character();
                
                if (current_input_character_is('\t')
                || current_input_character_is('\n')
                || current_input_character_is('\f')
                || current_input_character_is(' '))
                {
                }
                else if (current_input_character_is_ascii_alpha())
                {
                    auto& doctype { create_doctype_token() };
                    *doctype.m_name = lowercase(m_current_input_character);
                    switch_to(State::DoctypeName);
                }
                break;
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
                }
                else if (current_input_character_is('>'))
                {
                    switch_to(State::Data);
                    emit_current_token();
                    return;
                }
                else
                {
                    *current_doctype_token().m_name += m_current_input_character;
                }
                break;
            }
        }
    }
}

}
