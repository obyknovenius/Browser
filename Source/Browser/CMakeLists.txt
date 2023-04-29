set(BROWSER_SOURCES
    main.cpp
    WebView.cpp
    Window.cpp
)

add_executable(browser ${BROWSER_SOURCES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

target_link_libraries(browser PRIVATE css ${GTKMM_LIBRARIES})

target_include_directories(browser PUBLIC ${GTKMM_INCLUDE_DIRS})

target_compile_options(browser PUBLIC ${GTKMM_CFLAGS_OTHER})