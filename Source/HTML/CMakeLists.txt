set(HTML_SOURCES)

add_subdirectory(Parsing)

add_library(html STATIC ${HTML_SOURCES})
