//
//  String.h
//  Browser
//
//  Created by Vitaly Dyachkov on 30.03.22.
//

#pragma once

#include <string>
#include <string_view>

namespace Infra {

std::string ascii_lowercase(std::string_view string)
{
    std::string lowercast_string { string };
    lowercast_string.reserve(string.length());
    for (int code_point : string)
    {
        if (is_ascii_lower_alpha(code_point))
        {
            code_point += 0x0020;
        }
        lowercast_string.push_back(code_point);
    }
    return lowercast_string;
}

bool is_ascii_case_insensitive_match(const std::string_view a, const std::string_view b)
{
    return ascii_lowercase(a) == ascii_lowercase(b);
}

}
