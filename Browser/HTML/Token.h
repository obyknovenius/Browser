//
//  Token.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 22.12.21.
//

#pragma once

#include <string>
#include <list>
#include <iostream>

namespace HTML {

struct Attribute {
    std::string name {};
    std::string value {};
};

class Token {
public:
    virtual ~Token() {}
};

class DOCTYPE : public Token {
public:
    ~DOCTYPE() {}
    
    friend std::ostream& operator<<(std::ostream& out, const DOCTYPE& doctype);
};

class Tag : public Token {
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

class StartTag : public Tag {
public:
    ~StartTag() {}
    
    friend std::ostream& operator<<(std::ostream& out, const StartTag& start_tag);
};

class EndTag : public Tag {
public:
    ~EndTag() {}
    
    friend std::ostream& operator<<(std::ostream& out, const EndTag& end_tag);
};

class Comment : public Token {
    char m_data;
public:
    Comment(char data) : m_data { data } {}
    ~Comment() {}
    
    char data() { return m_data; };
    
    friend std::ostream& operator<<(std::ostream& out, const Comment& comment);
};

class Character : public Token {
    char m_data;
    
public:
    Character(char data) : m_data { data } {}
    ~Character() {}
    
    char data() { return m_data; };
    
    friend std::ostream& operator<<(std::ostream& out, const Character& character);
};

class EndOfFile : public Token {
    ~EndOfFile() {}
    
    friend std::ostream& operator<<(std::ostream& out, const EndOfFile& end_of_file);
};

};
