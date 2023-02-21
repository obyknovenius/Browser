cmake_minimum_required(VERSION 3.25)

project(Browser)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

add_executable(browser main.cpp Window.cpp WebView.cpp)

target_link_libraries(browser ${GTKMM_LIBRARIES})
target_include_directories(browser PUBLIC ${GTKMM_INCLUDE_DIRS})
target_compile_options(browser PUBLIC ${GTKMM_CFLAGS_OTHER})