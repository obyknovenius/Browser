//
//  Tokenizer.cpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#include "Tokenizer.h"

#include <iostream>

using namespace std;

namespace HTML {

int Tokenizer::consume_next_input_character() {
    int next_input_parameter;
    if (m_next_input_character) {
        next_input_parameter = *m_next_input_character;
        m_next_input_character = nullptr;
    } else {
        next_input_parameter = m_input_stream.get();
    }
    return next_input_parameter;
}

void Tokenizer::reconsume_in(State state, int* current_input_character) {
    m_next_input_character = current_input_character;
    m_state = state;
}

void Tokenizer::switch_to(State state) {
    m_state = state;
}

template <class T>
void Tokenizer::create_token() {
    m_current_token = new T{};
}

Tag* Tokenizer::current_tag_token() {
    return dynamic_cast<Tag*>(m_current_token);
}

void Tokenizer::emit(Token *token) {
    if (DOCTYPE* doctype = dynamic_cast<DOCTYPE*>(token)) {
        cout << "DOCTYPE";
    }
    if (StartTag* start_tag = dynamic_cast<StartTag*>(token)) {
        cout << "<" << start_tag->tag_name();
        for (Attribute attribute : start_tag->attributes()) {
            cout << " " << attribute.name << "=" << attribute.value;
        }
        cout << ">";
    }
    if (EndTag* end_tag = dynamic_cast<EndTag*>(token)) {
        cout << "</" << end_tag->tag_name() << ">";
    }
    if (Comment* comment = dynamic_cast<Comment*>(token)) {
        cout << "//" << comment->data;
    }
    if (Character* character = dynamic_cast<Character*>(token)) {
        cout << character->data();
    }
    if (EndOfFile* end_of_file = dynamic_cast<EndOfFile*>(token)) {
        cout << "end-of-file";
    }
    delete token;
}

void Tokenizer::tokenize() {
    int current_input_character;
    
    do {
        current_input_character = consume_next_input_character();
        
        switch (m_state) {
            case State::Data: {
                if (current_input_character == '<') {
                    switch_to(State::TagOpen);
                } else if (current_input_character == EOF) {
                    emit(new EndOfFile{});
                } else {
                    emit(new Character{(char)current_input_character});
                }
            } break;
                
            case State::TagOpen: {
                if (current_input_character == '/') {
                    switch_to(State::EndTagOpen);
                } else if (isascii(current_input_character)) {
                    create_token<StartTag>();
                    reconsume_in(State::TagName, &current_input_character);
                }
            } break;
        
            case State::EndTagOpen: {
                if (isascii(current_input_character)) {
                    create_token<EndTag>();
                    reconsume_in(State::TagName, &current_input_character);
                }
            } break;
        
            case State::TagName: {
                if (current_input_character == '\t' ||
                    current_input_character == '\n' ||
                    current_input_character == '\f' ||
                    current_input_character == ' ') {
                    switch_to(State::BeforeAttributeName);
                } else if (current_input_character == '>') {
                    switch_to(State::Data);
                    emit(current_tag_token());
                } else {
                    current_tag_token()->tag_name() += current_input_character;
                }
            } break;
        
            case State::BeforeAttributeName: {
                current_tag_token()->start_new_attribute();
                reconsume_in(State::AttributeName, &current_input_character);
                break;
            }
        
            case State::AttributeName: {
                if (current_input_character == '=') {
                    switch_to(State::BeforeAttributeValue);
                } else if (isascii(current_input_character)){
                    current_tag_token()->current_attribute()->name += current_input_character;
                }
                break;
            }
        
            case State::AfterAttributeName: {
                break;
            }
        
            case State::BeforeAttributeValue: {
                reconsume_in(State::AttributeValueUnquoted, &current_input_character);
                break;
            }
        
            case State::AttributeValueDoubleQuoted: {
                break;
            }
        
            case State::AttributeValueSingleQuoted: {
                break;
            }
        
            case State::AttributeValueUnquoted: {
                if (current_input_character == '>') {
                    switch_to(State::Data);
                    emit(current_tag_token());
                } else {
                    current_tag_token()->current_attribute()->value += current_input_character;
                }
                break;
            }
        
            case State::AfterAttributeValueQuoted: {
                break;
            }
        }
    } while(current_input_character != EOF);
}

}
