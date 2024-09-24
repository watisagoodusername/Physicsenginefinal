#pragma once
#include "rigidbody.h"
class rectcollide : public rigidbody { //class for rect rigidbody
    float sizex;
    float sizey;

public:
    rectcollide(float xsize, float ysize, float xpos, float ypos, float m = 1, float xvel = 0, float yvel = 0);

    void update(Vector2 mousepos, bool pressed, bool released);

    void draw();

    float get_xsize() { return sizex; }

    float get_ysize() { return sizey; }

    Vector2 get_vel() { return velocity; }

    Vector2 get_pos() { return position; }

    Vector2 get_corner();

    void set_vel(Vector2 v);
};

