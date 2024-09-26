#pragma once
#include "rigidbody.h"

class ballcollide : public rigidbody
{
    float radius;

public:
    ballcollide() {}
    ballcollide(float r, float xpos, float ypos, float m = 1, float xvel = 0, float yvel = 0);

    ~ballcollide();

    void ballcollision(ballcollide* compare);

    void update(Vector2 mousepos, bool press, bool release);

    void draw();

    const float get_r() { return radius; };
};

