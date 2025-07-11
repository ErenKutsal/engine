//
// Created by Ahmet Eren Kutsal on 10.07.2025.
//

#include "entity.h"

#include <stdint.h>
#include <string.h>

typedef struct
{
  bool alive;
  uint32_t generation;
} EntitySlot;

static EntitySlot entities[MAX_ENTITIES];

void entity_system_init()
{
  memset(entities, 0, sizeof(entities));
}

EntityID entity_create()
{
  for (int index = 0; index < MAX_ENTITIES; index++)
  {
    if (!entities[index].alive)
    {
      entities[index].alive = true;
      entities[index].generation++;
      return (EntityID) {.index = index, .generation = entities[index].generation};
    }
  }
  //There is no space, return invalid id
  return (EntityID) {.index = UINT32_MAX, .generation = 0};
}

void entity_destroy(const EntityID id)
{
  if (id.index >= MAX_ENTITIES) return;

  entities[id.index].alive = 0;
}

bool entity_is_alive(const EntityID id)
{
  if (id.index >= MAX_ENTITIES) return false;

  EntitySlot* slot = &entities[id.index];
  return slot->alive && slot->generation == id.generation;
}

uint32_t entity_get_generation(int index)
{
  return entities[index].generation;
}