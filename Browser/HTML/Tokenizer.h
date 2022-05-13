//
//  Tokenizer.h
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#pragma once

#include "Token.h"
#include <fstream>
#include <queue>
#include <string_view>

namespace HTML {

class Tokenizer final
{
public:
    Tokenizer(std::ifstream& input_stream) : m_input_stream { input_stream } {}
    
    std::queue<Token>& tokens() { return m_tokens; }
    
    void resume();
    
private:
    std::ifstream& m_input_stream;
    
    std::queue<Token> m_tokens {};
    
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
        
    Token m_current_token {};
    
    void switch_to(State state) { m_state = state; }
    
    int consume_next_input_character() { return m_input_stream.get(); }
    void reconsume_in(State state)
    {
        m_input_stream.unget();
        m_state = state;
    }
    
    std::string next_characters(int count);
    void consume_next_characters(int count);
    
    Token& create(Token::Type type) { return m_current_token = { type }; }
    
    void emit(const Token& token) { m_tokens.push(token); }
    void emit(char character) { m_tokens.push(character); }
};

}
