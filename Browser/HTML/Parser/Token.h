//
//  Token.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 22.12.21.
//

#pragma once

#include <string>
#include <optional>
#include <list>
#include <initializer_list>
#include <iostream>

namespace HTML
{

struct Attribute
{
    std::string name {};
    std::string value {};
};

class Token
{
public:
    enum class Type
    {
        Invalid,
        DOCTYPE,
        StartTag,
        EndTag,
        Comment,
        Character,
        EndOfFile,
    };
    
    Token() = default;
    Token(Type type) : m_type(type) {}
        
    bool is_doctype() const { return m_type == Type::DOCTYPE; }
    bool is_start_tag() const { return m_type == Type::StartTag; }
    bool is_end_tag() const { return m_type == Type::EndTag; }
    bool is_comment() const { return m_type == Type::Comment; }
    bool is_character() const { return m_type == Type::Character; }
    bool is_end_of_file() const { return m_type == Type::EndOfFile; }
    
    std::optional<std::string>& name() { return m_name; };
    const std::optional<std::string>& name() const { return m_name; };
    
    std::string& tag_name() { return m_tag_name; }
    const std::string& tag_name() const { return m_tag_name; }
    bool tag_name_is_one_of(std::initializer_list<std::string_view> tag_names) const;
    
    bool& self_closing_flag() { return m_self_closing_flag; }
    
    void start_new_attribute() { m_attributes.push_back(Attribute {}); }
    Attribute* current_attribute() { return &m_attributes.back(); }
    std::list<Attribute> attributes() { return m_attributes; }
    
    std::string& data() { return m_data; };
    const std::string& data() const { return m_data; };
    
    bool is_one_of(std::initializer_list<char> characters) const;
    
    friend std::ostream& operator<<(std::ostream& out, const Token& token);

private:
    Type m_type { Type::Invalid };
    
    // DOCTYPE
    struct
    {
        std::optional<std::string> m_name {};
    };
        
    // Start and end tag
    struct
    {
        std::string m_tag_name {};
        bool m_self_closing_flag { false };
        std::list<Attribute> m_attributes {};
    };
        
    // Comment and character
    struct
    {
        std::string m_data {};
    };
};

};
