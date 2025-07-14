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
        #include/ecs/systems/system_collision.h
        src/ecs/components/component_collider.c
        #include/ecs/components/component_collider.h
        src/ecs/systems/system_input.c
        #include/ecs/systems/system_input.h
        src/ecs/components/component_input.c
        #include/ecs/components/component_input.h
        src/ecs/components/component_tag.c
        #include/ecs/components/component_tag.h
        src/my_math.c
        #include/my_math.h
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
