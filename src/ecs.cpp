#include <numeric>
#include <ecs.hpp>
#include <sparse_set.hpp>

World createWorld(uint16 capacity) {
    World world;
    world.capacity = capacity;
    world.freeEntities = std::vector<Entity>(capacity);
    std::iota(world.freeEntities.begin(), world.freeEntities.end(), 0);
    world.health = createSparseSet<Health>(1000, 2000);
    world.positions = createSparseSet<Position>(1000, 2000);
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
    return health.get(entity);
}

Position* World::getPosition(Entity entity) {
    return positions.get(entity);
}

void World::setHealth(Entity entity, Health health) {
    this->health.insert(entity, health);
}

void World::setPosition(Entity entity, Position position) {
    positions.insert(entity, position);
}

void World::deleteEntity(Entity entity) {
    health.remove(entity);
    positions.remove(entity);
    freeEntities.push_back(entity);
}
