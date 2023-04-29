#include "Window.h"

#include "../CSS/Break/BoxFragment.h"
#include "../CSS/Break/FragmentedFlow.h"
#include "../CSS/Display/InlineBox.h"
#include "../CSS/Display/TextSequence.h"

#include <gtkmm.h>

namespace Browser {

WebView::WebView()
{
    set_draw_func(sigc::mem_fun(*this, &WebView::on_draw));
}

void WebView::on_draw(const Cairo::RefPtr<Cairo::Context>& context, int width, int height)
{
    double x = 0, y = 0;

    Cairo::FontExtents font_extents {};
    context->get_font_extents(font_extents);

    context->set_source_rgb(0.0, 0.0, 0.0);

    CSS::TextSequence text_sequence { "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vel sem erat. Praesent id odio ultrices, placerat erat vel, sollicitudin massa. Donec a leo vel lacus posuere tempor. In tincidunt, enim non blandit efficitur, leo eros cursus felis, quis efficitur odio felis a massa. Maecenas ipsum neque, congue et dolor a, sollicitudin venenatis ipsum. Quisque tristique enim nec est accumsan, at euismod nulla finibus. Nam quis feugiat ipsum. Etiam sagittis porta purus ut imperdiet. Vestibulum turpis erat, pulvinar quis tellus tincidunt, varius pharetra massa. Vestibulum imperdiet hendrerit ipsum vitae euismod." };
    
    CSS::InlineBox root_inline_box {};
    text_sequence.set_parent(&root_inline_box);

    CSS::FragmentedFlow fragmented_flow { root_inline_box, *context };

    while (fragmented_flow.has_next_fragment())
    {
        std::unique_ptr<CSS::BoxFragment> fragment { fragmented_flow.next_fragment(*context, width) };
        y += font_extents.height;
        context->move_to(0, y);
        context->show_text(fragment->text());
    }
}

}