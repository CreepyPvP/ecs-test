#include <stdio.h>
#include <ecs.hpp>
#include "sparse_set.hpp"


#if 1

static World myWorld;

void updatePositionSystem() {
    auto positions = myWorld.positions.list();
    while (positions.next()) {
        Position* position = positions.current;
        position->y -= 0.3;
    }
}

void updateHealthSystem() {
    auto positions = myWorld.positions.list();
    while (positions.next()) {
        Position* position = positions.current;
        Entity entity = positions.entity;

        if (position->y < 0) {
            Health* health = myWorld.health.get(entity);

            health->hp--;

            if (health->hp < 0) {
                myWorld.deleteEntity(entity);
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

    }

}

int main() {
    myWorld = createWorld(2000);

    for (int i = 0; i < 2000; ++i) {
        Entity entity = myWorld.createEntity();
        
        if (i % 2) {
            continue;
        }

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
        updatePositionSystem();
        updateHealthSystem();
    }
}
#endif

#if 0

int main() {
    SparseSet<Health> set = createSparseSet<Health>(5, 10);
    Health testHealth1 = { 1 };
    Health testHealth2 = { 2 };
    Health testHealth3 = { 3 };
    set.insert(0, testHealth1);
    set.insert(1, testHealth2);
    set.insert(2, testHealth3);
    set.remove(1);
    printf("%d\n", set.contains(2));
    printf("%d\n", set.contains(1));
}

#endif
