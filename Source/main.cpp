/* main.cpp
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

#include <gtkmm.h>

class BrowserWindow : public Gtk::Window
{
public:
    BrowserWindow();
};

BrowserWindow::BrowserWindow()
{
    set_title("Browser");
    set_default_size(640, 480);
}

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create("com.obyknovenius.Browser");
    return app->make_window_and_run<BrowserWindow>(argc, argv);
}
