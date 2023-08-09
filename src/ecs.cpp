#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <ecs.hpp>
#include <numeric>

World createWorld(uint32 capacity) {
    World world;
    world.capacity = capacity;
    world.health = (Health*) malloc(capacity * sizeof(Health));
    world.positions = (Position*) malloc(capacity * sizeof(Position));
    world.flags = (byte*) malloc(capacity * sizeof(byte));
    world.freeEntities = std::vector<Entity>(capacity);
    std::iota(world.freeEntities.begin(), world.freeEntities.end(), 0);

    for (int i = 0; i < capacity; ++i) {
        world.flags[i] = 0;
    }

    return world;
}

void World::deleteWorld() {
    free(health);
    free(positions);
    free(flags);
}

Entity World::createEntity() {
    assert(freeEntities.size() >= 1);
    Entity lastEntity = freeEntities.back();
    freeEntities.pop_back();
    flags[lastEntity] = IS_ACTIVE;
    return lastEntity;
}

Health* World::getHealth(Entity entity) {
    assert((flags[entity] & HEALTH) != 0);
    return health + entity;
}

Position* World::getPosition(Entity entity) {
    assert((flags[entity] & POSITION) != 0);
    return positions + entity;
}

void World::setHealth(Entity entity, Health health) {
    this->health[entity] = health;
    flags[entity] |= HEALTH;
}

void World::setPosition(Entity entity, Position position) {
    positions[entity] = position;
    flags[entity] |= POSITION;
}

void World::deleteEntity(Entity entity) {
    flags[entity] = 0;
    freeEntities.push_back(entity);
}

void World::filter(byte mask, void callback(Entity)) {
    mask = mask | IS_ACTIVE;
    for (Entity i = 0; i < capacity; ++i) {
        if ((flags[i] & mask) == mask) {
            callback(i);
        }
    }
}
