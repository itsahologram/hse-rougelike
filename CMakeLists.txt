cmake_minimum_required(VERSION 3.21)

project(hse-rougelike)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)



include(FetchContent)
FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)


FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)


include_directories(include)
add_executable(${CMAKE_PROJECT_NAME}
        src/main_menu.cpp
        src/characters.cpp
        src/map_generator.cpp
        src/button.cpp
        src/asset_manager.cpp
        src/engine.cpp
        src/view.cpp
        src/quest.cpp
        src/start_menu.cpp
        src/server.cpp
        src/client.cpp)


target_link_libraries(${CMAKE_PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-network)

target_link_libraries(${CMAKE_PROJECT_NAME} nlohmann_json::nlohmann_json)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS ${CMAKE_PROJECT_NAME})