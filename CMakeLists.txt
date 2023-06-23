cmake_minimum_required(VERSION 3.22)
project(TEST_SFML)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Wno-expansion-to-defined)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)


include_directories(include)
add_executable(TEST_SFML
        src/main.cpp
        src/characters.cpp
        src/map_generator.cpp
        src/button.cpp
        src/asset_manager.cpp
        src/engine.cpp
        src/view.cpp
        src/quest.cpp
        )

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 COMPONENTS system window graphics network REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(TEST_SFML sfml-system sfml-window sfml-graphics sfml-network)

find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(TEST_SFML nlohmann_json::nlohmann_json)
