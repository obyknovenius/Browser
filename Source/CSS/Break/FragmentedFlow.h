#pragma once

#include "../Display/Box.h"

#include <cairomm/cairomm.h>
#include <string>
#include <vector>

namespace CSS {

class Box;
class BoxFragment;

class FragmentedFlow final
{
public:
    FragmentedFlow(const Box& fragmentation_root);

    bool has_next_fragment() const { return m_new_line_word != m_words.cend(); }

    const BoxFragment* next_fragment(double remaining_fragmentainer_extent);

private:
    const Box& m_fragmentation_root;

    std::string m_text {};

    double m_whitespace_advance {};

    struct Word
    {
        const std::string::const_iterator begin {};
        const std::string::const_iterator end {};
        const double width {};
        const double height {};
    };

    std::vector<Word> m_words {};
    std::vector<Word>::const_iterator m_new_line_word {};
};

}
