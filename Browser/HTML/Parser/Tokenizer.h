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
#include <cassert>

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
    
    int m_current_input_character {};
    
    Token m_current_token {};
    
    void switch_to(State state) { m_state = state; }
    
    int consume_next_input_character() { return m_current_input_character = m_input_stream.get(); }
    void reconsume_in(State state)
    {
        m_input_stream.putback(m_current_input_character);
        m_state = state;
    }
    
    std::string next_characters(int count);
    void consume_next_characters(int count);
    
    Token& create_doctype_token()
    {
        return m_current_token = Token { Token::Type::DOCTYPE };
    }
    
    Token& create_start_tag_token()
    {
        return m_current_token = Token { Token::Type::StartTag };
    }
    
    Token& create_end_tag_token()
    {
        return m_current_token = Token { Token::Type::EndTag };
    }
    
    Token& create_comment_token(std::string_view data)
    {
        m_current_token = Token { Token::Type::Comment };
        m_current_token.m_data = data;
        return m_current_token;
    }
    
    Token& current_doctype_token()
    {
        assert(m_current_token.is_doctype());
        return m_current_token;
    }
    
    Token& current_tag_token()
    {
        assert(m_current_token.is_start_tag() || m_current_token.is_end_tag());
        return m_current_token;
    }
    
    Token& current_comment_token()
    {
        assert(m_current_token.is_comment());
        return m_current_token;
    }
    
    void emit_character_token(int character)
    {
        Token token = Token { Token::Type::Character };
        token.m_data = character;
        m_tokens.push(token);
    }
    
    void emit_end_of_file_token()
    {
        m_tokens.push(Token { Token::Type::EndOfFile });
    }
    
    void emit_current_token()
    {
        m_tokens.push(m_current_token);
    }
};

}
