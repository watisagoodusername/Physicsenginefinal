#pragma once
#include "include/rigidbody.h"
#include "include/PhysicsFunctions.h"
#include <raylib.h>
#include <raymath.h>

rigidbody::rigidbody() {
    size = Vector2{ 0, 0 };
    mass = 0;
    position = Vector2{ 0, 0 };
    velocity = Vector2{ 0, 0 };
    maxspeed = 50;
}
    
void rigidbody::clicked(Vector2 mousepos, float maxspeed) {
    Vector2 dif = Vector2Subtract(mousepos, position);
    velocity = dif;
    //position = Vector2Subtract(mousepos, dif);
}

void rigidbody::update(Vector2 mousepos) {
    if (held) {
        clicked(mousepos,maxspeed);
    }
    position = Vector2Add(position, velocity);
    wallbounce(0, 1000, 0, 1000, position, velocity, size.x / 2, size.y / 2);
}
void rigidbody::set_vel(Vector2 v) {
    velocity = v;
}
void rigidbody::set_pos(Vector2 p) {
    position = p;
}