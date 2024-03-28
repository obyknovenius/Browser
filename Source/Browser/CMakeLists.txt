set(BROWSER_SOURCES
    Application.cpp
    Window.cpp
    main.cpp
    WebView.cpp
)

add_executable(browser ${BROWSER_SOURCES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

target_link_libraries(browser PRIVATE html css ${GTKMM_LIBRARIES})

target_include_directories(browser PUBLIC ${GTKMM_INCLUDE_DIRS})

target_compile_options(browser PUBLIC ${GTKMM_CFLAGS_OTHER})

install(TARGETS browser DESTINATION bin)