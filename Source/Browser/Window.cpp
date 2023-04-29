#include "Window.h"

#include <gtkmm.h>

namespace Browser {

Window::Window()
{
    set_title("Browser");
    set_default_size(640, 480);

    set_child(m_web_view);
}

}