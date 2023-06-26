cmake_minimum_required(VERSION 3.21)
project(TEST_SFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)



include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)


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

#set(SFML_STATIC_LIBRARIES TRUE)
#find_package(SFML COMPONENTS graphics network REQUIRED)
target_link_libraries(TEST_SFML sfml-system sfml-window sfml-graphics sfml-network)
find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(TEST_SFML nlohmann_json::nlohmann_json)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET TEST_SFML POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:TEST_SFML> $<TARGET_FILE_DIR:TEST_SFML> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS TEST_SFML)