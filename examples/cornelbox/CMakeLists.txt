cmake_minimum_required(VERSION 3.20)

add_executable(cornelbox
main.cpp
)

target_link_libraries(cornelbox
PRIVATE
    ryt
)
