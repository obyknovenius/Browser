set(HTML_PARSING_SOURCES
    Parser.cpp
    StackOfOpenElements.cpp
    Token.cpp
    Tokenizer.cpp
    TreeConstructor.cpp
)

list(TRANSFORM HTML_PARSING_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

set(HTML_SOURCES ${HTML_SOURCES} ${HTML_PARSING_SOURCES} PARENT_SCOPE)