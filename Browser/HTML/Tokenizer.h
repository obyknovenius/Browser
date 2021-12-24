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
public:
    void tokenize();
private:
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
    
    ifstream m_input_stream { "/Users/obyknovenius/Developer/Personal/Browser/test.html" };
    int* m_next_input_character { nullptr };
        
    int consume_next_input_character();
    
    void switch_to(State);
    void reconsume_in(State, int*);
    
    Token* m_current_token;
    Tag* current_tag_token();
    
    template<class T>
    void create_token();
        
    void emit(Token*);

};

}
