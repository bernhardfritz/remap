include_directories(
    include
)

add_library(myassert STATIC
    src/myassert.c
)

add_executable(convert
    src/convert.c
    src/myassert.c
)
target_link_libraries(convert
    remap_library
    myassert
)

add_executable(diff
    src/diff.c
)
target_link_libraries(diff
    remap_library
    myassert
)
