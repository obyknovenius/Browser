#include "Window.h"

#include <gtkmm.h>

namespace Browser {

Window::Window(const Glib::RefPtr<Gio::File>& file)
{
    set_title("Browser");
    set_default_size(640, 480);

    m_web_view = new WebView(file->get_path());

    set_child(*m_web_view);
}

}
