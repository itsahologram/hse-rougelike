cmake_minimum_required(VERSION 3.22)
project(TEST_SFML)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(TEST_SFML
        src/main.cpp
        src/characters.cpp
        src/map_generator.cpp
        src/animation.cpp
        include/animation.hpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
set(SFML_INCLUDE_DIR C:/SFML-2.5.1/lib/cmake/SFML/include)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML-2.5.1/include)
target_link_libraries(TEST_SFML sfml-system sfml-window sfml-graphics sfml-audio)
