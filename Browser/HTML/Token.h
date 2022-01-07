//
//  Token.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 22.12.21.
//

#pragma once

#include <string>
#include <list>

namespace HTML {

struct Attribute {
    std::string name {};
    std::string value {};
};

class Token {
public:
    virtual ~Token() {}
};

struct DOCTYPE : public Token {
    ~DOCTYPE() {}
};

class Tag : public Token {
public:
    ~Tag() {}
    
    std::string& tag_name() { return m_tag_name; }
    
    bool& self_closing() { return m_self_closing; }
    
    void start_new_attribute() { m_attributes.push_back(Attribute{}); }
    Attribute* current_attribute() { return m_attributes.empty() ? nullptr : &m_attributes.back(); }
    std::list<Attribute> attributes() { return m_attributes; }
private:
    std::string m_tag_name {};
    
    bool m_self_closing { false };
    
    std::list<Attribute> m_attributes {};
};

struct StartTag : public Tag {
    ~StartTag() {}
};

struct EndTag : Tag {
    ~EndTag() {}
};

struct Comment : public Token {
    char data;
    ~Comment() {}
};

class Character : public Token {
public:
    Character(char data) : m_data(data) {}
    ~Character() {}
    
    char data() { return m_data; };
private:
    char m_data;
};

struct EndOfFile : public Token {
    ~EndOfFile() {}
};

};
