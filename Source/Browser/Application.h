/*
 * BrowserApplication.h
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

#pragma once

#include "Window.h"

#include <gtkmm.h>

namespace Browser {

class Application final : public Gtk::Application
{
public:
    static Glib::RefPtr<Application> create();

    Window* create_window(const Glib::RefPtr<Gio::File>& file);

protected:
    Application() : Gtk::Application("com.github.obyknovenius.Browser", Gio::Application::Flags::HANDLES_OPEN) {}

    void on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint) override;
};

}
