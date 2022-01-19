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
                
                if (at('<')) {
                    switch_to(State::TagOpen);
                    break;
                }
                
                if (at(EOF)) {
                    emit(new EndOfFile{});
                    break;
                }
                
                emit(new Character{(char)current_input_character()});
                break;
            }
                
            case State::TagOpen: {
                consume_next_input_character();
                
                if (at('/')) {
                    switch_to(State::EndTagOpen);
                    break;
                }
                
                if (at_ascii_alpha()) {
                    create_token<StartTag>();
                    reconsume_in(State::TagName);
                    break;
                }
            }
        
            case State::EndTagOpen: {
                consume_next_input_character();
                
                if (at_ascii_alpha()) {
                    create_token<EndTag>();
                    reconsume_in(State::TagName);
                    break;
                }
                
                break;
            }
        
            case State::TagName: {
                consume_next_input_character();
                
                if (at('\t') || at('\n') || at('\f') || at(' ')) {
                    switch_to(State::BeforeAttributeName);
                    break;
                }
                
                if (at('>')) {
                    switch_to(State::Data);
                    emit(current_tag_token());
                    break;
                }
                
                current_tag_token()->tag_name() += current_input_character();
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
                
                if (at('=')) {
                    switch_to(State::BeforeAttributeValue);
                    break;
                }
                
                if (at_ascii_upper_alpha()){
                    current_tag_token()->current_attribute()->name += lowercase_current_input_character();
                    break;
                }
                
                current_tag_token()->current_attribute()->name += current_input_character();
                
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
                
                if (at('>')) {
                    switch_to(State::Data);
                    emit(current_tag_token());
                    break;
                }
                
                current_tag_token()->current_attribute()->value += current_input_character();
                break;
            }
        
            case State::AfterAttributeValueQuoted: {
                consume_next_input_character();
                
                break;
            }
        }
    } while(!at(EOF));
}

}
