#pragma once
#include "rigidbody.h"
class rectcollide : public rigidbody { //class for rect rigidbody
    Vector2 size;

public:
    rectcollide(float xsize, float ysize, float xpos, float ypos, float m = 1, float xvel = 0, float yvel = 0);

    void rectcollision(rectcollide* compare);

    void update(Vector2 mousepos, bool pressed, bool released);

    void draw();

    float get_xsize() { return size.x; }

    float get_ysize() { return size.y; }

    Vector2 get_size() { return size; }

    Vector2 get_vel() { return velocity; }

    Vector2 get_pos() { return position; }

    Vector2 get_corner();

    void set_vel(Vector2 v);
};

