#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <ecs.hpp>
#include <numeric>
#include <unordered_map>

World createWorld(uint32 capacity) {
    World world;
    world.capacity = capacity;
    world.health = std::unordered_map<Entity, Health>();
    world.positions = std::unordered_map<Entity, Position>();
    world.freeEntities = std::vector<Entity>(capacity);
    std::iota(world.freeEntities.begin(), world.freeEntities.end(), 0);

    return world;
}

void World::deleteWorld() {

}

Entity World::createEntity() {
    assert(freeEntities.size() >= 1);
    Entity lastEntity = freeEntities.back();
    freeEntities.pop_back();
    return lastEntity;
}

Health* World::getHealth(Entity entity) {
    return &(health.at(entity));
}

Position* World::getPosition(Entity entity) {
    return &(positions.at(entity));
}

void World::setHealth(Entity entity, Health health) {
    this->health[entity] = health;
}

void World::setPosition(Entity entity, Position position) {
    positions[entity] = position;
}

void World::deleteEntity(Entity entity) {
    health.erase(entity);
    positions.erase(entity);
    freeEntities.push_back(entity);
}

void World::filterPosition(void callback(Entity)) {
    for (auto& entry : positions) {
        callback(entry.first);
    }
}

void World::filterHealth(void callback(Entity)) {
    for (auto& entry : health) {
        callback(entry.first);
    }
}
