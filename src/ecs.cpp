#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <ecs.hpp>

World createWorld(uint32 capacity) {
    World world;
    world.capacity = capacity;
    world.health = (Health*) malloc(capacity * sizeof(Health));
    world.positions = (Position*) malloc(capacity * sizeof(Position));
    world.flags = (byte*) malloc(capacity * sizeof(byte));

    for (int i = 0; i < capacity; ++i) {
        world.flags[i] = 0;
    }

    return world;
}

void deleteWorld(World* world) {
    free(world->health);
    free(world->positions);
    free(world->flags);
}

Entity createEntity(World* world) {
    for (Entity i = 0; i < world->capacity; ++i) {
        if ((world->flags[i] & IS_ACTIVE) == 0) {
            world->flags[i] = IS_ACTIVE;
            return i;
        }
    }

    throw "Capacity exceeded";
}

Health* getHealth(World* world, Entity entity) {
    assert((world->flags[entity] & HEALTH) != 0);
    return world->health + entity;
}

Position* getPosition(World* world, Entity entity) {
    assert((world->flags[entity] & POSITION) != 0);
    return world->positions + entity;
}

void setHealth(World* world, Entity entity, Health health) {
    world->health[entity] = health;
    world->flags[entity] |= HEALTH;
}

void setPosition(World* world, Entity entity, Position position) {
    world->positions[entity] = position;
    world->flags[entity] |= POSITION;
}

void deleteEntity(World *world, Entity entity) {
    world->flags[entity] = 0;
}

void filter(World* world, byte mask, void callback(Entity)) {
    mask = mask | IS_ACTIVE;
    for (Entity i = 0; i < world->capacity; ++i) {
        if ((world->flags[i] & mask) == mask) {
            callback(i);
        }
    }
}
