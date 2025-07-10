cmake_minimum_required(VERSION 3.31)
project(engine C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET SDL2_image)

if (NOT SDL2_IMAGE_INCLUDE_DIRS)
    set(SDL2_IMAGE_INCLUDE_DIRS /opt/homebrew/include)
endif()

set(SOURCES
        main.c
        engine/engine.c
        engine/renderer.c
        engine/input.c
        ecs/entity.c
        ecs/component.c
)

add_executable(game ${SOURCES})

# Proper modern include path setting
target_include_directories(game PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(game
        ${SDL2_LIBRARIES}
        PkgConfig::SDL2_image
)
