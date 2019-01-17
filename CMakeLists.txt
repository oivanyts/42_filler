cmake_minimum_required(VERSION 3.12)
project(filler C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wextra -Werror -Wall")

set(SOURCE_FILES
        src/filler.c
        includes/filler_header.h
        )
add_executable(filler ${SOURCE_FILES})

target_link_libraries(filler ${CMAKE_SOURCE_DIR}/libft/libft.a)