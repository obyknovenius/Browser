#pragma once

#include "WebView.h"

#include <gtkmm.h>

namespace Browser {

class Window final : public Gtk::Window
{
public:
    Window();

protected:
    WebView m_web_view {};
};

}
