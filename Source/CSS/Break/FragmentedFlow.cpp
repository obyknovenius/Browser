#include "FragmentedFlow.h"

#include "../Display/Box.h"
#include "../Display/TextSequence.h"
#include "BoxFragment.h"

#include <algorithm>
#include <cassert>

namespace CSS {

FragmentedFlow::FragmentedFlow(const Box& fragmentation_root) : m_fragmentation_root { fragmentation_root }
{
    const TextSequence* text_sequence { reinterpret_cast<const TextSequence*>(fragmentation_root.first_child()) };
    m_text = text_sequence->text();

    Cairo::TextExtents whitespace_extents {};
    m_fragmentation_root.font()->get_text_extents(" ", whitespace_extents);
    m_whitespace_advance = whitespace_extents.x_advance;

    auto previous_soft_wrap_opportunity { m_text.cbegin() - 1 };
    for (auto character { m_text.cbegin() }; character <= m_text.cend(); ++character)
    {
        if (*character == ' ' || character == m_text.cend())
        {
            std::string word { previous_soft_wrap_opportunity + 1, character };
            Cairo::TextExtents extents {};
            m_fragmentation_root.font()->get_text_extents(word, extents);

            m_words.push_back({ previous_soft_wrap_opportunity + 1, character, extents.width, extents.height });

            previous_soft_wrap_opportunity = character;
        }
    }

    m_new_line_word = m_words.cbegin();
}

const BoxFragment* FragmentedFlow::next_fragment(double remaining_fragmentainer_extent)
{
    assert(has_next_fragment());

    Cairo::FontExtents font_extents {};
    m_fragmentation_root.font()->get_extents(font_extents);
    double fragment_height { font_extents.height };

    double fragment_width { 0 };
    for (auto word { m_new_line_word }; word < m_words.cend(); ++word)
    {
        double width = word->width;
        if (word != m_new_line_word)
            width += m_whitespace_advance;

        if ((fragment_width + width) > remaining_fragmentainer_extent)
        {
            if (word == m_new_line_word)
                return nullptr;

            std::string fragment_text { m_new_line_word->begin, (word - 1)->end };
            m_new_line_word = word;
            return new BoxFragment(m_fragmentation_root, fragment_text, fragment_width, fragment_height);
        }

        fragment_width += width;
    }

    std::string fragment_text { m_new_line_word->begin, m_text.cend() };
    m_new_line_word = m_words.end();
    return new BoxFragment(m_fragmentation_root, fragment_text, fragment_width, fragment_height);
}

}
