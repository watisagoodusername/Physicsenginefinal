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

    void clicked(Vector2 mousepos, float maxspeed);

    void update(Vector2 mousepos);

    void draw();

    float get_m();

    Vector2 get_vel();

    Vector2 get_pos();

    void set_vel(Vector2 v);

    void set_pos(Vector2 p);

};

