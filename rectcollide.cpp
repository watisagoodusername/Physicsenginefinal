#include "include/rectcollide.h"
#include "include/rigidbody.h"
#include "include/PhysicsFunctions.h"
#include "raylib.h"
#include <iostream>

rectcollide::rectcollide(float xsize, float ysize, float xpos, float ypos, float m, float xvel, float yvel) {
    size.x = xsize;
    size.y = ysize;
    mass = xsize * ysize * m;
    position.x = xpos;
    position.y = ypos;
    velocity.x = xvel;
    velocity.y = yvel;
    maxspeed = 50;
}

void rectcollide::rectcollision(rectcollide* compare) {
    Vector2 p1 = position;
    Vector2 p2 = compare->get_pos();// position values

    Vector2 s1 = size;
    Vector2 s2 = compare->get_size();

    if (rectoverlap(p1, p2, s1, s2)) {
        Vector2 dif = Vector2Subtract(p1, p2);// distance between circles

        Vector2 v1 = velocity;
        Vector2 v2 = compare->get_vel(); //velocity values, passed by value

        float angle = atan2(dif.x, dif.y);

        float m1 = mass;
        float m2 = compare->get_m();// mass

        if (dif.x + 15 < (s1.x + s2.x) / 2) {
            v1.y *= -1;
            v2.y *= -1;
            std::cout << "x overlap\n";
        }
        if (dif.y + 15 < (s1.y + s2.y) / 2) {
            v1.x *= -1;
            v2.x *= -1;
            std::cout << "y overlap\n";
        }

        velocity = v1;
        compare->set_vel(v2);//applies velocity
    }
}

void rectcollide::update(Vector2 mousepos, bool pressed, bool released) {
    if (pinrect(mousepos, position, size) && !held && pressed) {
        held = true;
    }
    if (held && released) {
        held = false;
        velocity = Vector2ClampValue(velocity, 0, maxspeed);
    }

    rigidbody::update(mousepos);

    wallbounce(0, 1000, 0, 1000, position, velocity, size.x / 2, size.y / 2);
}

void rectcollide::draw() {
    DrawRectangle(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y, BLACK);
    DrawRectangle(position.x - size.x / 2 + 5, position.y - size.y / 2 + 5, size.x - 10, size.y - 10, DARKBLUE);
}

Vector2 rectcollide::get_corner() {
    Vector2 cornerpos;
    cornerpos.x = position.x - size.x / 2;
    cornerpos.y = position.y - size.y / 2;
    return cornerpos;
}

void rectcollide::set_vel(Vector2 v) {
    velocity = v;
}