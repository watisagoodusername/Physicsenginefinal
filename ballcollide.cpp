#include "include/ballcollide.h"
#include "include/rigidbody.h"
#include <raylib.h>
#include "include/PhysicsFunctions.h"

ballcollide::ballcollide(float r, float xpos, float ypos, float m, float xvel, float yvel) {
    radius = r;
    size = Vector2{ r * 2, r * 2 };
    mass = 3 * r * r * m;
    position.x = xpos;
    position.y = ypos;
    velocity.x = xvel;
    velocity.y = yvel;
    maxspeed = 50;
}

void ballcollide::update(Vector2 mousepos, bool pressed, bool released) {
    if (pincircle(mousepos, position, radius) && !held && pressed) {
        held = true;
    }
    if (held && released) {
        held = false;
        velocity = Vector2ClampValue(velocity, 0, maxspeed);
    }

    rigidbody::update(mousepos);
}

void ballcollide::draw() {
    DrawCircleV(position, radius, BLACK);
    DrawCircleV(position, radius - 5, DARKBLUE);
}
