#include "Window.h"

namespace Browser {

WebView::WebView()
{
    set_draw_func(sigc::mem_fun(*this, &WebView::on_draw));
}

void WebView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->select_font_face("Times", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
    cr->set_font_size(18.0);
    cr->move_to(20.0, 30.0);
    cr->show_text("Hello World!");
}

}