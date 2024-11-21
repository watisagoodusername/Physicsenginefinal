#pragma once
#include "rigidbody.h"
#include "ballcollide.h"
class rectcollide : public rigidbody { //class for rect rigidbody
    Vector2 size;

public:
    rectcollide(float xsize, float ysize, float xpos, float ypos, float m = 1, float xvel = 0, float yvel = 0);

    void rectballcollision(ballcollide* compare);

    void rectballposition(ballcollide* compare);

    void rectcollision(rectcollide* compare);

    void rectposition(rectcollide* compare);

    void update(Vector2 gravity, Vector2 mousepos, bool pressed, bool released);

    void walls();

    void draw(camera cam);

    float get_xsize() { return size.x; }

    float get_ysize() { return size.y; }

    Vector2 get_size() { return size; }

    Vector2 get_vel() { return velocity; }

    Vector2 get_pos() { return position; }

    Vector2 get_corner(int num = 0);

    Vector2 posfromcorner(Vector2 c, int num = 0);

    void set_vel(Vector2 v);
};

