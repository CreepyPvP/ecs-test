#pragma once

#include <vector>
#include "sparse_set.hpp"

static const byte IS_ACTIVE = 0b1;
static const byte HEALTH = 0b10;
static const byte POSITION = 0b100;


typedef uint16 Entity;

struct Position {
    float x;
    float y;
    float z;
};

struct Health {
    int hp;
};

struct World {
    uint32 capacity;

    SparseSet<Health> health;
    SparseSet<Position> positions;

    std::vector<Entity> freeEntities;

    void deleteWorld();
    Entity createEntity();
    void deleteEntity(Entity entity);
    Health* getHealth(Entity entity);
    Position* getPosition(Entity entity);
    void setPosition(Entity entity, Position position);
    void setHealth(Entity entity, Health health);
};

World createWorld(uint16 capacity);

