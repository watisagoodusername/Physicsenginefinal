#include "include/createobject.h"

Vector2 createobject::size() {
    Vector2 s;
    s.x = abs(start.x - end.x);
    s.y = abs(start.y - end.y);
    return s;
}

createobject::createobject(std::string otype) {
    objecttype = otype;
    start.x = 0;
    start.y = 0;
    end.x = 0;
    end.y = 0;
    centre.x = 0;
    centre.y = 0;
    active = false;
}

float createobject::radius() {
    return abs(start.x - end.x) / 2;
}

void createobject::initcreation(Vector2 mousepos) {
    start = mousepos;
    active = true;
}

ballcollide createobject::finishcreationb(Vector2 mousepos) {//creates a ball collider
    end = mousepos;
    active = false;

    Vector2 s = size();

    if (start.x < end.x) { centre.x = start.x + s.x / 2; }
    else { centre.x = end.x + s.x / 2; }
    if (start.y < end.y) { centre.y = start.y + s.y / 2; }
    else { centre.y = end.y + s.y / 2; }

    return ballcollide(radius(), centre.x, centre.y);
}

rectcollide createobject::finishcreationr(Vector2 mousepos) {//creates a rectangle collider
    end = mousepos;
    active = false;

    Vector2 s = size();

    if (start.x < end.x) { centre.x = start.x + s.x / 2; }
    else { centre.x = end.x + s.x / 2; }
    if (start.y < end.y) { centre.y = start.y + s.y / 2; }
    else { centre.y = end.y + s.y / 2; }

    return rectcollide(s.x, s.y, centre.x, centre.y);
}

void createobject::draw(Vector2 mousepos) {
    if (active) {
        Vector2 pos = get_centre(mousepos);
        if (objecttype == "ball") {
            DrawCircleV(pos, radius(), DARKGRAY);
        }
        else {
            pos.x -= static_cast<int>((mousepos.x - get_start().x) / 2);
            pos.y -= static_cast<int>((mousepos.y - get_start().y) / 2);
            DrawRectangle(pos.x, pos.y, static_cast<int>(mousepos.x - get_start().x), static_cast<int>(mousepos.y - get_start().y), DARKGRAY);
        }
    }
}

Vector2 createobject::get_centre(Vector2 mousepos) {//center position for circle creation
    end = mousepos;

    Vector2 s = size();

    if (start.x < end.x) { centre.x = start.x + s.x / 2; }
    else { centre.x = end.x + s.x / 2; }
    if (start.y < end.y) { centre.y = start.y + s.y / 2; }
    else { centre.y = end.y + s.y / 2; }

    return centre;
}