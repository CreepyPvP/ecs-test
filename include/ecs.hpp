#pragma once

#include <cstdint>
#include <vector>

#define uint16 uint16_t
#define uint32 uint32_t
#define byte unsigned char

static const byte IS_ACTIVE = 0b1;
static const byte HEALTH = 0b10;
static const byte POSITION = 0b100;

// struct Archtype {
//     uint32 componentFlags; 
//     uint16 capacity;
//     byte* components;
// };
//
// struct Entity {
//     uint16 index;
//     uint16 generation;
//     uint16 archtype;
// };


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
    Position* positions;
    Health* health;
    byte* flags;
    uint32 capacity;

    std::vector<Entity> freeEntities;

    void deleteWorld();
    Entity createEntity();
    void deleteEntity(Entity entity);
    Health* getHealth(Entity entity);
    Position* getPosition(Entity entity);
    void setPosition(Entity entity, Position position);
    void setHealth(Entity entity, Health health);
    void filter(byte mask, void callback(Entity));
};

World createWorld(uint32 capacity);

