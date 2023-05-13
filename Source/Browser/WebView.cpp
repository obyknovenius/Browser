#include "Window.h"

#include "../CSS/Break/BoxFragment.h"
#include "../CSS/Display/InlineBox.h"
#include "../CSS/Display/TextSequence.h"
#include "../CSS/Inline/InlineFormattingContext.h"
#include "../CSS/Inline/LineBox.h"

#include <gtkmm.h>

namespace Browser {

WebView::WebView()
{
    set_draw_func(sigc::mem_fun(*this, &WebView::on_draw));
}

void WebView::on_draw(const Cairo::RefPtr<Cairo::Context>& context, int width, int height)
{
    const Cairo::RefPtr<Cairo::ToyFontFace> font_face { Cairo::ToyFontFace::create("serif", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL) };
    const Cairo::RefPtr<Cairo::ScaledFont> font { Cairo::ScaledFont::create(font_face, Cairo::scaling_matrix(16, 16), context->get_matrix()) };

    CSS::InlineBox root_inline_box { font };

    CSS::TextSequence text_sequence { "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vel sem erat. Praesent id odio ultrices, placerat erat vel, sollicitudin massa. Donec a leo vel lacus posuere tempor. In tincidunt, enim non blandit efficitur, leo eros cursus felis, quis efficitur odio felis a massa. Maecenas ipsum neque, congue et dolor a, sollicitudin venenatis ipsum. Quisque tristique enim nec est accumsan, at euismod nulla finibus. Nam quis feugiat ipsum. Etiam sagittis porta purus ut imperdiet. Vestibulum turpis erat, pulvinar quis tellus tincidunt, varius pharetra massa. Vestibulum imperdiet hendrerit ipsum vitae euismod." };
    text_sequence.set_parent(&root_inline_box);

    CSS::InlineFormattingContext inline_formatting_context { root_inline_box };
    inline_formatting_context.layout(width);

    double y { 0 };

    Cairo::FontExtents font_extents {};
    font->get_extents(font_extents);

    context->set_source_rgb(0.0, 0.0, 0.0);

    for (const CSS::LineBox *line_box : inline_formatting_context.line_boxes())
    {
        y += font_extents.height;
        context->move_to(0, y);

        for (const CSS::BoxFragment* fragment : line_box->fragments())
        {
            context->set_scaled_font(fragment->box().font());
            context->show_text(fragment->text());
        }
    }
}

}
