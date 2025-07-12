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
        #main.c
        game/game.c
        engine/engine.c
        engine/renderer.c
        engine/input.c
        engine/ecs/entity.c
        engine/ecs/components/component.c
        engine/ecs/components/component_transform.c
        engine/ecs/components/component_sprite.c
        engine/ecs/systems/system_movement.c
        engine/ecs/systems/system_render.c
        engine/ecs/ecs_init.c
        engine/ecs/systems/system_collision.c
        engine/ecs/systems/system_collision.h
        engine/ecs/components/component_collider.c
        engine/ecs/components/component_collider.h
        engine/ecs/systems/system_input.c
        engine/ecs/systems/system_input.h
        engine/ecs/components/component_input.c
        engine/ecs/components/component_input.h
        engine/ecs/components/component_tag.c
        engine/ecs/components/component_tag.h
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
