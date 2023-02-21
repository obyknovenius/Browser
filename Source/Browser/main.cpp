#include <gtkmm.h>

#include "Window.h"

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create("com.obyknovenius.Browser");
    return app->make_window_and_run<Browser::Window>(argc, argv);
}