//
//  Tokenizer.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#pragma once

#include <fstream>

#include "Token.h"

namespace HTML {

class Tokenizer {
    
    enum class State {
        Data,
        TagOpen,
        EndTagOpen,
        TagName,
        BeforeAttributeName,
        AttributeName,
        AfterAttributeName,
        BeforeAttributeValue,
        AttributeValueDoubleQuoted,
        AttributeValueSingleQuoted,
        AttributeValueUnquoted,
        AfterAttributeValueQuoted,
    };
    
    State m_state { State::Data };
    
    std::ifstream m_input_stream { "/Users/obyknovenius/Developer/Personal/Browser/test.html" };
    
    int m_next_input_character { m_input_stream.get() };
    int m_current_input_character {};
    bool m_reconsume { false };
    
    Token* m_current_token;
    
    int consume_next_input_character();
    
    State state() { return m_state; }
    void switch_to(State state) { m_state = state; }
    void reconsume_in(State state)
    {
        m_reconsume = true;
        m_state = state;
    }
    
    template<class T>
    void create_token() { m_current_token = new T {}; }
    
    Tag* current_tag_token() { return static_cast<Tag*>(m_current_token); }
    
public:
    Token* next_token();
};

}
