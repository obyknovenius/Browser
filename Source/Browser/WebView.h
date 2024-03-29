#pragma once

#include <gtkmm.h>

namespace Browser {

class WebView final : public Gtk::DrawingArea
{
public:
    WebView(const std::string& filename);

private:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
};

}
