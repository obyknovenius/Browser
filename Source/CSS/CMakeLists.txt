set(CSS_SOURCES)

add_subdirectory(Break)
add_subdirectory(Display)

add_library(css STATIC ${CSS_SOURCES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIROMM REQUIRED cairomm-1.16)

target_link_libraries(css PRIVATE ${CAIROMM_LIBRARIES})

target_include_directories(css PUBLIC ${CAIROMM_INCLUDE_DIRS})

target_compile_options(css PUBLIC ${CAIROMM_CFLAGS_OTHER})