set(HTML_SOURCES)

add_subdirectory(Parsing)

add_library(html STATIC ${HTML_SOURCES})

target_link_libraries(html PRIVATE infra dom)