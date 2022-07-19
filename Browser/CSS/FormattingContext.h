//
//  FormattingContext.h
//  Browser
//
//  Created by Vitaly Dyachkov on 18.07.22.
//

#pragma once

namespace CSS {

class FormattingContext
{
public:
    virtual ~FormattingContext() {};
    
    void layout();
};

}
