#include <stdio.h>

#include <ecs.hpp>

static World myWorld;

void updatePositionSystem(Entity e) {
    Position* position = myWorld.getPosition(e);
    position->y -= 0.3;
}

void updateHealthSystem(Entity e) {
    Position* position = myWorld.getPosition(e);
    Health* health = myWorld.getHealth(e);

    if (position->y < 0) {
        health->hp--;
    }

    if (health->hp < 0) {
        myWorld.deleteEntity(e);
        Entity entity = myWorld.createEntity();

        Health health = {
            .hp = 10
        };
        myWorld.setHealth(entity, health);

        Position pos = {
            .x = 0,
            .y = 100,
            .z = 10,
        };
        myWorld.setPosition(entity, pos);
    }
}

int main() {
    myWorld = createWorld(1000);

    for (int i = 0; i < 1000; ++i) {
        Entity entity = myWorld.createEntity();
        Health health = {
            .hp = 10
        };
        myWorld.setHealth(entity, health);

        Position pos = {
            .x = (float) i,
            .y = 100 + (float) (i % 50),
            .z = 10,
        };
        myWorld.setPosition(entity, pos);
    }

    for (int i = 0; i < 1000000; ++i) {
        myWorld.filter(POSITION, updatePositionSystem);
        myWorld.filter(POSITION | HEALTH, updateHealthSystem);
    }
}
