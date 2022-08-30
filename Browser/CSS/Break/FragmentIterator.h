//
//  FragmentIterator.h
//  Browser
//
//  Created by Vitaly Dyachkov on 30.08.22.
//

#pragma once

#include "Fragment.h"
#include "../../Graphics/Font.h"
#include <string>
#include <optional>

namespace CSS {

class FragmentIterator final
{
public:
    FragmentIterator(const std::string& fragmented_flow, const Graphics::Font& font) : m_fragmented_flow { fragmented_flow } , m_font { font } {}
    
    std::optional<Fragment> next_fragment(double remaining_fragmentainer_extent);

private:
    const std::string& m_fragmented_flow;
    
    const Graphics::Font& m_font;
    
    size_t m_pos { 0 };
};

}
