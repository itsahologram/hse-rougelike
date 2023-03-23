cmake_minimum_required(VERSION 3.23)
project(TEST_SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(TEST_SFML
        main.cpp
        characters.cpp
        characters.hpp
        map.hpp
        map_generator.hpp
        map_generator.cpp
        )

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML-2.5.1/include)
target_link_libraries(TEST_SFML sfml-system sfml-window sfml-graphics sfml-audio)
