#include "Application.h"
#include "Window.h"

#include <gtkmm.h>

int main(int argc, char** argv)
{
    Glib::RefPtr<Browser::Application> application = Browser::Application::create();
    return application->run(argc, argv);
}
