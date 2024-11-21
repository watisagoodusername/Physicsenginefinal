#pragma once
#include <raylib.h>

class rigidbody
{
protected:
    float mass;
    Vector2 velocity;
    Vector2 position;
    bool held = false;
    int maxspeed;
    bool active = true;
    bool grounded = false;

    Vector2 changevelocity;
    Vector2 changeposition;

public:
    rigidbody();
    ~rigidbody() {}

    void clicked(Vector2 mousepos, float maxspeed);

    void update(Vector2 gravity, Vector2 mousepos);

    void applychanges();

    const float get_m() { return mass; };

    const Vector2 get_vel() { return velocity; };

    const Vector2 get_pos() { return position; };

    void set_vel(Vector2 v);

    void set_pos(Vector2 p);

    bool &get_ground() { return grounded; };

    void set_ground(bool g) { grounded = g; };
};

