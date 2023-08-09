#include <stdio.h>

#include <ecs.hpp>

static World myWorld;

void updatePositionSystem(Entity e) {
    Position* position = getPosition(&myWorld, e);
    position->y -= 0.3;
}

void updateHealthSystem(Entity e) {
    Position* position = getPosition(&myWorld, e);
    Health* health = getHealth(&myWorld, e);

    if (position->y < 0) {
        health->hp--;
    }

    if (health->hp < 0) {
        deleteEntity(&myWorld, e);
        Entity entity = createEntity(&myWorld);

        Health health = {
            .hp = 10
        };
        setHealth(&myWorld, entity, health);

        Position pos = {
            .x = 0,
            .y = 100,
            .z = 10,
        };
        setPosition(&myWorld, entity, pos);
    }
}

int main() {
    myWorld = createWorld(1000);

    for (int i = 0; i < 1000; ++i) {
        Entity entity = createEntity(&myWorld);
        Health health = {
            .hp = 10
        };
        setHealth(&myWorld, entity, health);

        Position pos = {
            .x = (float) i,
            .y = 100 + (float) (i % 50),
            .z = 10,
        };
        setPosition(&myWorld, entity, pos);
    }

    for (int i = 0; i < 1000000; ++i) {
        filter(&myWorld, POSITION, updatePositionSystem);
        filter(&myWorld, POSITION | HEALTH, updateHealthSystem);
    }
}
