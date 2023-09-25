
add_subdirectory(math)

set(SRC main.cpp)
target_sources(main PRIVATE ${SRC})

target_sources(test_concept PRIVATE test_concept.cpp)
