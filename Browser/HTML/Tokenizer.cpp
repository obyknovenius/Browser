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

Token* Tokenizer::next_token() {
    while (true) {
        switch (m_state) {
            case State::Data: {
                consume_next_input_character();
                
                if (at('<')) {
                    switch_to(State::TagOpen);
                    break;
                }
                
                if (at(EOF)) {
                    return new EndOfFile{};
                }
                
                return new Character{(char)current_input_character()};
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
                    return current_tag_token();
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
                    return current_tag_token();
                }
                
                current_tag_token()->current_attribute()->value += current_input_character();
                break;
            }
        
            case State::AfterAttributeValueQuoted: {
                consume_next_input_character();
                
                break;
            }
        }
    }
}

}
