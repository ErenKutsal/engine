//
// Created by Ahmet Eren Kutsal on 10.07.2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <stdbool.h>
#include <stdint.h>

#define MAX_ENTITIES 1024
#define ENTITY_NONE (EntityID) {UINT32_MAX, UINT32_MAX}

typedef struct
{
    uint32_t index;
    uint32_t generation;
} EntityID;

void entity_system_init();
EntityID entity_create();
void entity_destroy(EntityID id);
bool entity_is_alive(EntityID id);
uint32_t entity_get_generation(int index);

#endif //ENTITY_H
