#pragma once
#include "rigidbody.h"

class ballcollide : public rigidbody
{
    float radius;

public:
    ballcollide(float r, float xpos, float ypos, float m = 1, float xvel = 0, float yvel = 0);

    void update(Vector2 mousepos, bool press, bool release);

    void draw();

    const float get_r() { return radius; };
};

