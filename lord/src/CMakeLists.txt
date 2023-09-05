cmake_minimum_required(VERSION 3.27.2)


set(SRC main.cpp)

target_sources(main PRIVATE ${SRC})

add_subdirectory(strutil)
add_subdirectory(math)
