set(DOM_SOURCES
    Document.cpp
    Element.cpp
    Node.cpp
)

list(TRANSFORM DOM_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

add_library(dom STATIC ${DOM_SOURCES})

target_link_libraries(dom PRIVATE infra)
