//
//  TreeConstruction.h
//  Browser
//
//  Created by Vitaly Dyachkov on 22.02.22.
//

#pragma once

#include "Token.h"

namespace HTML {

class TreeConstruction {
public:
    bool dispatch(Token* token);
};

}
