cmake_minimum_required(VERSION 3.28)
project(Connect4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Connect4 main.cpp
        Board.h
        Game.h
        Token.h)
target_compile_features(Connect4 PRIVATE cxx_std_17)
target_link_libraries(Connect4 PRIVATE SFML::Graphics SFML::Window SFML::System)