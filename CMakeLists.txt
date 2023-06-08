cmake_minimum_required(VERSION 3.22)
project(TEST_SFML)

set(CMAKE_CXX_STANDARD 17)

set(nlohmann_json_DIR C:/msys64/mingw64/share/cmake/nlohmann_json)
find_package(nlohmann_json 3.2.0 REQUIRED)


include_directories(include)

add_executable(TEST_SFML
        src/main.cpp
        src/characters.cpp
        src/map_generator.cpp
        src/animation.cpp
        include/animation.hpp include/quest.hpp src/button.cpp include/button.hpp src/asset_manager.cpp include/asset_manager.hpp src/engine.cpp include/engine.hpp src/view.cpp src/quest.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
set(SFML_INCLUDE_DIR C:/SFML-2.5.1/include/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML-2.5.1/include)
target_link_libraries(TEST_SFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)


set(nlohmann_json_DIR C:/msys64/mingw64/share/cmake/nlohmann_json)
find_package(nlohmann_json 3.2.0 REQUIRED)
include_directories(C:/msys64/mingw64/include)
