#include "include/rectcollide.h"
#include "include/rigidbody.h"
#include "include/PhysicsFunctions.h"
#include "raylib.h"

rectcollide::rectcollide(float xsize, float ysize, float xpos, float ypos, float m, float xvel, float yvel) {
    sizex = xsize;
    sizey = ysize;
    mass = xsize * ysize * m;
    position.x = xpos;
    position.y = ypos;
    velocity.x = xvel;
    velocity.y = yvel;
    maxspeed = 50;
}

void rectcollide::update(Vector2 mousepos, bool pressed, bool released) {
    if (pinrect(mousepos, position, Vector2 {sizex, sizey}) && !held && pressed) {
        held = true;
    }
    if (held && released) {
        held = false;
        velocity = Vector2ClampValue(velocity, 0, maxspeed);
    }

    rigidbody::update(mousepos);
}

void rectcollide::draw() {
    DrawRectangle(position.x - sizex / 2, position.y - sizey / 2, sizex, sizey, BLACK);
}

Vector2 rectcollide::get_corner() {
    Vector2 cornerpos;
    cornerpos.x = position.x - sizex / 2;
    cornerpos.y = position.y - sizey / 2;
    return cornerpos;
}

void rectcollide::set_vel(Vector2 v) {
    velocity = v;
}