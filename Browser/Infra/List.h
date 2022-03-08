//
//  List.hpp
//  Browser
//
//  Created by Vitaly Dyachkov on 04.03.22.
//

#pragma once

namespace Infra {

template <typename T>
class List
{
public:
    virtual void append(T item) = 0;
};

}
