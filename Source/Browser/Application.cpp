/*
 * BrowserApplication.cpp
 *
 * Copyright 2023 Vitaly Dyachkov <obyknovenius@me.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Application.h"

#include "Window.h"

namespace Browser {

Glib::RefPtr<Application> Application::create()
{
    return Glib::make_refptr_for_instance<Application>(new Application());
}

Window* Application::create_window(const Glib::RefPtr<Gio::File>& file)
{
    Window* window = new Window(file);

    add_window(*window);

    return window;
}

void Application::on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint)
{
    Window* window = nullptr;

    auto windows = get_windows();
    if (windows.size() > 0)
    {
        window = dynamic_cast<Window*>(windows[0]);
    }

    if (!window)
    {
        window = create_window(files[0]);
    }

    window->present();
}

}
