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

void ballcollide::ballcollision(ballcollide* compare) {
    Vector2 p1 = position;
    Vector2 p2 = compare->get_pos();// position values

    float r1 = radius;
    float r2 = compare->get_r();

    if (circleoverlap(p1, p2, r1, r2)) {
        Vector2 dif = Vector2Subtract(p1, p2);// distance between circles

        float angle = atan2(dif.x, dif.y);

        Vector2 v1 = velocity;
        Vector2 v2 = compare->get_vel(); //velocity values, passed by value

        float m1 = mass;
        float m2 = compare->get_m();// mass

        bounce(v1, v2, m1, m2, angle, 0.95);//velocity calculations
        resolvecirclecollision(p1, p2, r1, r2, m1, m2);//changes p1 and p2 so they arent inside each other

        position = p1;
        compare->set_pos(p2);//applies position

        velocity = v1;
        compare->set_vel(v2);//applies velocity
    }
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
