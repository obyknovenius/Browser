//
//  Tokenizer.hpp
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

class Tokenizer
{
public:
    Tokenizer(std::ifstream& input_stream) : m_input_stream { input_stream } {}
    
    std::queue<Token>& tokens() { return m_tokens; }
    
    void resume();
    
private:
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
    
    Token m_current_token {};
        
    std::queue<Token> m_tokens {};
    
    void switch_to(State state) { m_state = state; }
    void reconsume_in(State state)
    {
        m_input_stream.unget();
        m_state = state;
    }
    
    void consume_next_input_character() { m_current_input_character = m_input_stream.get(); }
    
    int current_input_character() { return m_current_input_character; }
    
    bool current_input_character_is(int character) { return current_input_character() == character; }
    bool current_input_character_is_ascii_alpha() { return isalpha(current_input_character()); }
    bool current_input_character_is_ascii_upper_alpha() { return isupper(current_input_character()); }
    
    bool next_few_characters_are(const std::string_view characters);
    bool next_few_characters_are_ascii_case_insensitive(const std::string_view characters);
    void consume_those_characters();
    
    Token& create_doctype_token()
    {
        m_current_token = Token { Token::Type::DOCTYPE };
        return m_current_token;
    }
    
    Token& create_start_tag_token()
    {
        m_current_token = Token { Token::Type::StartTag };
        return m_current_token;
    }
    
    Token& create_end_tag_token()
    {
        m_current_token = Token { Token::Type::EndTag };
        return m_current_token;
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
    
    void emit_current_input_character_as_character_token()
    {
        Token token = Token { Token::Type::Character };
        token.m_data = m_current_input_character;
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
