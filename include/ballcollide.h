#pragma once
#include "rigidbody.h"
#include "include/camera.h"

class ballcollide : public rigidbody
{
    float radius;

public:
    ballcollide(float r, float xpos, float ypos, float m = 1, float xvel = 0, float yvel = 0);

    void ballcollision(ballcollide* compare, Vector2 gravity);

    void update(Vector2 gravity, Vector2 mousepos, bool press, bool release);

    void ballposition(ballcollide* compare);

    void walls();

    void draw(camera cam);

    const float get_r() { return radius; };
};

