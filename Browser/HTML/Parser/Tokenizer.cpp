//
//  Tokenizer.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#include "Tokenizer.h"
#include "../../Infra/CodePoint.h"
#include "../../Infra/String.h"
#include <cstdio>

namespace HTML {

using namespace Infra;

std::string Tokenizer::next_characters(int count)
{
    std::string characters {};
    characters.resize(count);
    
    std::streampos pos = m_input_stream.tellg();
    m_input_stream.read(characters.data(), count);
    m_input_stream.seekg(pos);
    
    return characters;
}

void Tokenizer::consume_next_characters(int count)
{
    for ( int i { 0 }; i < count; ++i)
    {
        consume_next_input_character();
    }
}

void Tokenizer::resume()
{
    for(;;)
    {
        switch (m_state)
        {
            case State::Data:
            {
                auto character { consume_next_input_character() };
                
                if (character == '<')
                {
                    switch_to(State::TagOpen);
                }
                else if (character == EOF)
                {
                    emit_end_of_file_token();
                    return;
                }
                else
                {
                    emit_character_token(m_current_input_character);
                    return;
                }
                break;
            }
            case State::TagOpen:
            {
                auto character { consume_next_input_character() };
                
                if (character == '!')
                {
                    switch_to(State::MarkupDeclarationOpen);
                }
                else if (character == '/')
                {
                    switch_to(State::EndTagOpen);
                }
                else if (is_ascii_alpha(character))
                {
                    auto& start_tag { create_start_tag_token() };
                    start_tag.m_tag_name = "";
                    reconsume_in(State::TagName);
                }
                break;
            }
            case State::EndTagOpen:
            {
                auto character { consume_next_input_character() };
                
                if (is_ascii_alpha(character))
                {
                    auto& end_tag { create_end_tag_token() };
                    end_tag.m_tag_name = "";
                    reconsume_in(State::TagName);
                }
                break;
            }
            case State::TagName:
            {
                auto character { consume_next_input_character() };
                
                if (character == '\t'
                || character == '\n'
                || character == '\f'
                || character == ' ')
                {
                    switch_to(State::BeforeAttributeName);
                }
                else if (character == '>')
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
                auto character { consume_next_input_character() };
                
                if (character == '=')
                {
                    switch_to(State::BeforeAttributeValue);
                }
                else if (is_ascii_upper_alpha(character))
                {
                    current_tag_token().current_attribute().name += (m_current_input_character + 0x0020);
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
                auto character { consume_next_input_character() };
                
                if (character == '>')
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
                if (next_characters(2) == "--")
                {
                    consume_next_characters(2);
                    create_comment_token("");
                    switch_to(State::CommentStart);
                }
                else if (is_ascii_case_insensitive_match(next_characters(7), "DOCTYPE"))
                {
                    consume_next_characters(7);
                    switch_to(State::Doctype);
                }
                break;
            }
            case State::CommentStart:
            {
                auto character { consume_next_input_character() };
                
                if (character == '-')
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
                auto character { consume_next_input_character() };
                
                if (character == '-')
                {
                    switch_to(State::CommentEnd);
                }
                break;
            }
            case State::Comment:
            {
                auto character { consume_next_input_character() };
                
                if (character == '-')
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
                auto character { consume_next_input_character() };
                
                if (character == '-')
                {
                    switch_to(State::CommentEnd);
                }
                break;
            }
            case State::CommentEnd:
            {
                auto character { consume_next_input_character() };
                
                if (character == '>')
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
                auto character { consume_next_input_character() };
                
                if (character == '\t'
                || character == '\n'
                || character == '\f'
                || character == ' ')
                {
                    switch_to(State::BeforeDoctypeName);
                }
                else if (character == '>')
                {
                    reconsume_in(State::BeforeDoctypeName);
                }
                break;
            }
            case State::BeforeDoctypeName:
            {
                auto character { consume_next_input_character() };
                
                if (character == '\t'
                || character == '\n'
                || character == '\f'
                || character == ' ')
                {
                }
                else if (is_ascii_upper_alpha(character))
                {
                    auto& doctype { create_doctype_token() };
                    doctype.m_name = { static_cast<char>(m_current_input_character + 0x0020) };
                    switch_to(State::DoctypeName);
                }
                else
                {
                    auto& doctype { create_doctype_token() };
                    doctype.m_name = { static_cast<char>(m_current_input_character) };
                    switch_to(State::DoctypeName);
                }
                break;
            }
            case State::DoctypeName:
            {
                auto character { consume_next_input_character() };
                
                if (character == '\t'
                || character == '\n'
                || character == '\f'
                || character == ' ')
                {
                    switch_to(State::AfterDoctypeName);
                }
                else if (character == '>')
                {
                    switch_to(State::Data);
                    emit_current_token();
                    return;
                }
                else if (is_ascii_upper_alpha(character))
                {
                    *current_doctype_token().m_name += (m_current_input_character + 0x0020);
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
