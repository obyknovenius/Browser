cmake_minimum_required(VERSION 3.25)

project(Browser)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(CSS)
add_subdirectory(HTML)
add_subdirectory(Browser)

install(FILES ../test.html DESTINATION usr/share/browser)