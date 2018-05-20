cmake_minimum_required(VERSION 2.6)
project(remap)

include_directories(
    include
    lib/stb/include
)

add_library(remap_library
    src/color.c
    src/convert.c
    src/diff.c
)
set_target_properties(remap_library
    PROPERTIES OUTPUT_NAME remap
)

add_executable(remap_executable
    src/remap.c
)
target_link_libraries(remap_executable
    remap_library
)
set_target_properties(remap_executable
    PROPERTIES OUTPUT_NAME remap
)

add_subdirectory(test)

install(TARGETS remap_executable DESTINATION bin)