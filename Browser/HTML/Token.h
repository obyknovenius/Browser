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
    virtual ~Token() {}
    
    template<class T>
    T as() { return dynamic_cast<T>(this); }
};

class Doctype : public Token
{
    std::optional<std::string> m_name;

public:
    explicit Doctype(char character) : m_name { std::string { character } } {}
    ~Doctype() {}
    
    std::optional<std::string>& name() { return m_name; };
    const std::optional<std::string>& name() const { return m_name; };
    
    friend std::ostream& operator<<(std::ostream& out, const Doctype& doctype);
};

class Tag : public Token
{
protected:
    std::string m_tag_name {};
    
    bool m_self_closing { false };
    
    std::list<Attribute> m_attributes {};
    
public:
    ~Tag() {}
    
    std::string& tag_name() { return m_tag_name; }
    
    bool& self_closing() { return m_self_closing; }
    
    void start_new_attribute() { m_attributes.push_back(Attribute {}); }
    Attribute* current_attribute() { return &m_attributes.back(); }
    std::list<Attribute> attributes() { return m_attributes; }
};

class StartTag : public Tag
{
public:
    ~StartTag() {}
    
    friend std::ostream& operator<<(std::ostream& out, const StartTag& start_tag);
};

class EndTag : public Tag
{
public:
    ~EndTag() {}
    
    friend std::ostream& operator<<(std::ostream& out, const EndTag& end_tag);
};

class Comment : public Token
{
    std::string m_data;

public:
    Comment(std::string data) : m_data { data } {}
    ~Comment() {}
    
    std::string& data() { return m_data; };
    const std::string& data() const { return m_data; };
    
    friend std::ostream& operator<<(std::ostream& out, const Comment& comment);
};

class Character : public Token
{
    char m_data;

public:
    Character(char data) : m_data { data } {}
    ~Character() {}
    
    char data() { return m_data; };
    
    bool is_one_of(std::initializer_list<char> characters);
    
    friend std::ostream& operator<<(std::ostream& out, const Character& character);
};

class EndOfFile : public Token
{
    ~EndOfFile() {}
    
    friend std::ostream& operator<<(std::ostream& out, const EndOfFile& end_of_file);
};

};
