//
//  Parser.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 04.01.22.
//

#pragma once

#include "Token.h"

namespace HTML {

enum class InsertionMode {
    Initial,
};

struct ParseState {
    InsertionMode m_insertion_mode { InsertionMode::Initial };
};

class Parser {
    ParseState m_parse_state;
public:
    void process(Token* token);
};

}
