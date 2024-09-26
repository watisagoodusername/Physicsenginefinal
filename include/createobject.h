#pragma once
#include "raylib.h"
#include <iostream>
#include "include/ballcollide.h"
#include "include/rectcollide.h"

class createobject {//contains information about object to be created 
private:
    Vector2 start;
    Vector2 end;
    Vector2 centre;

    Vector2 size();

public:
    bool active;
    std::string objecttype;

    createobject(std::string otype);

    float radius();

    void initcreation(Vector2 mousepos);

    ballcollide finishcreationb(Vector2 mousepos);

    rectcollide finishcreationr(Vector2 mousepos);

    void draw(Vector2 mousepos);

    Vector2 get_start() { return start; }

    Vector2 get_centre(Vector2 mousepos);

    std::string get_object() { return objecttype; }
};

