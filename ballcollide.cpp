#include "include/ballcollide.h"
#include "include/rigidbody.h"
#include <raylib.h>
#include "include/PhysicsFunctions.h"

ballcollide::ballcollide(float r, float xpos, float ypos, float m, float xvel, float yvel) {
    ballcollide::radius = r;
    ballcollide::size = Vector2{ r * 2, r * 2 };
    ballcollide::mass = 3 * r * r * m;
    ballcollide::position.x = xpos;
    ballcollide::position.y = ypos;
    ballcollide::velocity.x = xvel;
    ballcollide::velocity.y = yvel;
    ballcollide::maxspeed = 25;
}

void ballcollide::update(Vector2 mousepos, bool pressed, bool released) {
    if (pincircle(mousepos, ballcollide::position, ballcollide::radius) && !held && pressed) {
        held = true;
    }
    if (held && released) {
        held = false;
        velocity = Vector2ClampValue(velocity, 0, maxspeed);
    }

    rigidbody::update(mousepos);
}

void ballcollide::draw() {
    DrawCircleV(ballcollide::position, radius, BLACK);
    DrawCircleV(ballcollide::position, radius - 5, DARKBLUE);
}

float ballcollide::get_r() {
    return radius;
}