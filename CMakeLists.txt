
cmake_minimum_required(VERSION 3.5)

project(game_of_life LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_executable(game_of_life
    src/main.cpp
    src/gameoflife.cpp
    src/gameoflife.h
    src/wireworld.cpp
    src/wireworld.h
    src/starwars.cpp
    src/starwars.h
    src/entityswitch.cpp
    src/entityswitch.h
    )


include(${CMAKE_CURRENT_LIST_DIR}/e172/e172.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/sdl_implementation/sdl_implementation.cmake)
target_link_libraries(game_of_life
    e172
    sdl_impl
)
