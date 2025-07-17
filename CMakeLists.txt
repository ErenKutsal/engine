cmake_minimum_required(VERSION 3.31)
project(src C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET SDL2_image)

if (NOT SDL2_IMAGE_INCLUDE_DIRS)
    set(SDL2_IMAGE_INCLUDE_DIRS /opt/homebrew/include)
endif()

set(SOURCES
        game/game.c
        src/engine.c
        src/renderer.c
        src/input.c
        src/ecs/entity.c
        src/ecs/components/component.c
        src/ecs/components/component_transform.c
        src/ecs/components/component_sprite.c
        src/ecs/systems/system_movement.c
        src/ecs/systems/system_render.c
        src/ecs/ecs_init.c
        src/ecs/systems/system_collision.c
        src/ecs/components/component_collider.c
        src/ecs/systems/system_input.c
        src/ecs/components/component_input.c
        src/ecs/components/component_tag.c
        src/my_math.c
        src/key_binding.c
        include/key_binding.h
        game/player.c
        include/camera.h
        src/camera.c
        src/map/map_parser.c
        src/map/map_loader.c
        src/map/map.c
        include/map/map.h
        include/map/map_loader.h
        include/map/map_parser.h
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
        m
)
