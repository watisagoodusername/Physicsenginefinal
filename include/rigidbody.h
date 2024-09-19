#pragma once
#include <raylib.h>

class rigidbody
{
protected:
    float mass;
    Vector2 size;
    Vector2 velocity;
    Vector2 position;
    bool held = false;
    int maxspeed;

public:
    rigidbody();
    ~rigidbody() {}

    void clicked(Vector2 mousepos, float maxspeed);

    void update(Vector2 mousepos);

    const float get_m() { return mass; };

    const Vector2 get_vel() { return velocity; };

    const Vector2 get_pos() { return position; };

    void set_vel(Vector2 v);

    void set_pos(Vector2 p);

};

