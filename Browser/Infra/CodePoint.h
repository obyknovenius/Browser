//
//  CodePoint.h
//  Browser
//
//  Created by Vitaly Dyachkov on 30.03.22.
//

#pragma once

namespace Infra {

inline bool is_ascii_upper_alpha(int code_point)
{
    return code_point >= 'A' && code_point <= 'Z';
}

inline bool is_ascii_lower_alpha(int code_point)
{
    return code_point >= 'a' && code_point <= 'z';
}

inline bool is_ascii_alpha(int code_point)
{
    return is_ascii_upper_alpha(code_point) || is_ascii_lower_alpha(code_point);
}

}
