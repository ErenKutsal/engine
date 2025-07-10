//
// Created by Ahmet Eren Kutsal on 10.07.2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <stdbool.h>
#include <stdint.h>

#define MAX_ENTITIES 1024

typedef struct
{
    uint32_t index;
    uint32_t generation;
} EntityID;

void entity_system_init();
EntityID entity_create();
void entity_destroy(EntityID id);
bool entity_is_alive(EntityID id);

#endif //ENTITY_H
