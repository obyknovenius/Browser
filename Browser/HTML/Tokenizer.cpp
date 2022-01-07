//
//  Tokenizer.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#include "Tokenizer.h"

#include <iostream>

namespace HTML {

void Tokenizer::consume_next_input_character() {
    if (m_reconsume) {
        m_reconsume = false;
        return;
    }
    m_current_input_character = m_next_input_character;
    m_next_input_character = m_input_stream.get();
}

bool Tokenizer::is(int character) {
    return m_current_input_character == character;
}

void Tokenizer::reconsume_in(State state) {
    m_reconsume = true;
    m_state = state;
}

void Tokenizer::switch_to(State state) {
    m_state = state;
}

template <class T>
void Tokenizer::create_token() {
    m_current_token = new T {};
}

Tag* Tokenizer::current_tag_token() {
    return dynamic_cast<Tag*>(m_current_token);
}

void Tokenizer::emit(Token* token) {
    if (DOCTYPE* doctype = dynamic_cast<DOCTYPE*>(token)) {
        std::cout << "DOCTYPE";
    }
    
    if (StartTag* start_tag = dynamic_cast<StartTag*>(token)) {
        std::cout << "<" << start_tag->tag_name();
        for (Attribute attribute : start_tag->attributes()) {
            std::cout << " " << attribute.name << "=" << attribute.value;
        }
        std::cout << ">";
    }
    
    if (EndTag* end_tag = dynamic_cast<EndTag*>(token)) {
        std::cout << "</" << end_tag->tag_name() << ">";
    }
    
    if (Comment* comment = dynamic_cast<Comment*>(token)) {
        std::cout << "//" << comment->data;
    }
    
    if (Character* character = dynamic_cast<Character*>(token)) {
        std::cout << character->data();
    }
    
    if (EndOfFile* end_of_file = dynamic_cast<EndOfFile*>(token)) {
        std::cout << "end-of-file";
    }
    
    delete token;
}

void Tokenizer::tokenize() {
    do {
        switch (m_state) {
            case State::Data: {
                consume_next_input_character();
                
                if (is('<')) {
                    switch_to(State::TagOpen);
                    break;
                }
                
                if (is(EOF)) {
                    emit(new EndOfFile{});
                    break;
                }
                
                emit(new Character{(char)m_current_input_character});
                break;
            }
                
            case State::TagOpen: {
                consume_next_input_character();
                
                if (is('/')) {
                    switch_to(State::EndTagOpen);
                    break;
                }
                
                if (isascii(m_current_input_character)) {
                    create_token<StartTag>();
                    reconsume_in(State::TagName);
                    break;
                }
            }
        
            case State::EndTagOpen: {
                consume_next_input_character();
                
                if (isascii(m_current_input_character)) {
                    create_token<EndTag>();
                    reconsume_in(State::TagName);
                    break;
                }
                
                break;
            }
        
            case State::TagName: {
                consume_next_input_character();
                
                if (is('\t') || is('\n') || is('\f') || is(' ')) {
                    switch_to(State::BeforeAttributeName);
                    break;
                }
                
                if (is('>')) {
                    switch_to(State::Data);
                    emit(current_tag_token());
                    break;
                }
                
                current_tag_token()->tag_name() += m_current_input_character;
                break;
            }
        
            case State::BeforeAttributeName: {
                consume_next_input_character();
                
                current_tag_token()->start_new_attribute();
                reconsume_in(State::AttributeName);
                break;
            }
        
            case State::AttributeName: {
                consume_next_input_character();
                
                if (is('=')) {
                    switch_to(State::BeforeAttributeValue);
                    break;
                }
                
                if (isascii(m_current_input_character)){
                    current_tag_token()->current_attribute()->name += m_current_input_character;
                    break;
                }
                
                break;
            }
        
            case State::AfterAttributeName: {
                consume_next_input_character();
                
                break;
            }
        
            case State::BeforeAttributeValue: {
                consume_next_input_character();
                
                reconsume_in(State::AttributeValueUnquoted);
                break;
            }
        
            case State::AttributeValueDoubleQuoted: {
                consume_next_input_character();
                
                break;
            }
        
            case State::AttributeValueSingleQuoted: {
                consume_next_input_character();
                
                break;
            }
        
            case State::AttributeValueUnquoted: {
                consume_next_input_character();
                
                if (is('>')) {
                    switch_to(State::Data);
                    emit(current_tag_token());
                    break;
                }
                
                current_tag_token()->current_attribute()->value += m_current_input_character;
                break;
            }
        
            case State::AfterAttributeValueQuoted: {
                consume_next_input_character();
                
                break;
            }
        }
    } while(m_current_input_character != EOF);
}

}
