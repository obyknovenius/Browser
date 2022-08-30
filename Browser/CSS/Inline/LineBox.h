//
//  LineBox.h
//  Browser
//
//  Created by Vitaly Dyachkov on 15.07.22.
//

#pragma once

#include "../Break/Fragment.h"
#include <vector>

namespace CSS {

class LineBox
{
public:
    void append(Fragment fragment);
    
    const std::vector<Fragment>& fragments() const { return m_fragments; }

private:
    std::vector<Fragment> m_fragments {};
};

}
