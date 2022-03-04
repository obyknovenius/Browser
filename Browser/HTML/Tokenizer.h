//
//  Tokenizer.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#pragma once

#include "Token.h"
#include <fstream>

namespace HTML {

class Tokenizer
{
    enum class State
    {
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
        MarkupDeclarationOpen,
        CommentStart,
        CommentStartDash,
        Comment,
        CommentEndDash,
        CommentEnd,
        CommentEndBang,
        Doctype,
        BeforeDoctypeName,
        DoctypeName,
        AfterDoctypeName,
        AfterDoctypePublicKeyword,
        BeforeDoctypePublicIdentifier,
        DoctypePublicIdentifierDoubleQuoted,
        DoctypePublicIdentifierSingleQuoted,
        AfterDoctypePublicIdentifier,
        BetweenDoctypePublicAndSystemIdentifiers,
        AfterDoctypeSystemKeyword,
        BeforeDoctypeSystemIdentifier,
        DoctypeSystemIdentifierDoubleQuoted,
        DoctypeSystemIdentifierSingleQuoted,
        AfterDoctypeSystemIdentifier,
        BogusDoctype,
    };
    
    State m_state { State::Data };
    
    std::ifstream& m_input_stream;
    
    int m_current_input_character {};
    size_t m_number_of_characters_to_consume {};
        
    Token* m_current_token {};
    
    void switch_to(State state) { m_state = state; }
    void reconsume_in(State state)
    {
        m_input_stream.unget();
        m_state = state;
    }
    
    void consume_next_input_character()
    {
        m_current_input_character = m_input_stream.get();
    }
    
    int current_input_character() {
        return m_current_input_character;
    }
    
    bool current_input_character_is(int character)
    {
        return current_input_character() == character;
    }
    
    bool current_input_character_is_ascii_alpha()
    {
        return isalpha(current_input_character());
    }
    
    bool current_input_character_is_ascii_upper_alpha()
    {
        return isupper(current_input_character());
    }
    
    bool next_few_characters_are(const std::string_view characters);
    
    bool next_few_characters_are_ascii_case_insensitive(const std::string_view characters);
    
    void consume_those_characters();
    
    template<typename T, typename... Args>
    void create_token(Args... args)
    {
        m_current_token = new T { args... };
    }
    
    template<typename T>
    T current_token()
    {
        return static_cast<T>(m_current_token);
    }
    
public:
    Tokenizer(std::ifstream& input_stream) : m_input_stream { input_stream } {}
    
    void operator>>(Token**);
};

}
