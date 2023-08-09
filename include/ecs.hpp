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
};

World createWorld(uint32 capacity);
void deleteWorld(World* world);

Entity createEntity(World* world);
void deleteEntity(World* world, Entity entity);

Health* getHealth(World* world, Entity entity);
Position* getPosition(World* world, Entity entity);

void setPosition(World* world, Entity entity, Position position);
void setHealth(World* world, Entity entity, Health health);

void filter(World* world, byte mask, void callback(Entity));
