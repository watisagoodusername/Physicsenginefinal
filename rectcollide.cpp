#include "include/rectcollide.h"
#include "include/rigidbody.h"
#include "include/PhysicsFunctions.h"
#include "raylib.h"
#include <iostream>

rectcollide::rectcollide(float xsize, float ysize, float xpos, float ypos, float m, float xvel, float yvel) {
    size.x = xsize;
    size.y = ysize;
    mass = xsize * ysize * m;
    position.x = xpos;
    position.y = ypos;
    velocity.x = xvel;
    velocity.y = yvel;
    maxspeed = 50;
}

void rectcollide::rectcollision(rectcollide* compare) {
    Vector2 p1 = position;
    Vector2 p2 = compare->get_pos();// position values

    Vector2 s1 = size;
    Vector2 s2 = compare->get_size();

    if (rectoverlap(p1, p2, s1, s2)) {
        //when collision occures
        Vector2 dif = Vector2{ p1.x - p2.x, p1.y - p2.y};// distance between circles

        Vector2 v1 = velocity;
        Vector2 v2 = compare->get_vel(); //velocity values, passed by value

        float m1 = mass;
        float m2 = compare->get_m();// mass

        float xoverlap, yoverlap;

        xoverlap = (s1.x + s2.x) / 2 - abs(dif.x);
        yoverlap = (s1.y + s2.y) / 2 - abs(dif.y); // how far the squares overlapped

        if (v1.x != 0 or v1.y != 0 or v2.x != 0 or v2.y != 0) {// make sure both velocities arent 0 to avoid division by 0 errors

            // finding which side overlapped first
            float xscalefac;
            float yscalefac;

            xscalefac = xoverlap / (abs(v1.x - v2.x));
            yscalefac = yoverlap / (abs(v1.y - v2.y));//what portion of a frame the objects have been overlapped for. one of these will always be between 0 and 1 
            //whichever one of these variables is smaller is the axis of the collision

            Vector2 sendoutsidev1;
            Vector2 sendoutsidev2;

            if (xscalefac < yscalefac) {//finding the distance to move to send the objects to the moment of collision
                // if x has a lower scalefac that means the collision was on the x axis 
                sendoutsidev1 = Vector2 { v1.x * -xscalefac, v1.y * -xscalefac };
                sendoutsidev2 = Vector2 { v2.x * -xscalefac, v2.y * -xscalefac };//moves by the velocity * scalefac
            }
            else {
                sendoutsidev1 = Vector2 { v1.x * -yscalefac, v1.y * -yscalefac };
                sendoutsidev2 = Vector2 { v2.x * -yscalefac, v2.y * -yscalefac };
            }

            p1.x += sendoutsidev1.x;
            p1.y += sendoutsidev1.y;
            p2.x += sendoutsidev2.x;
            p2.y += sendoutsidev2.y;

            if (xscalefac < yscalefac) {
                bounce1D(v1.x, v2.x, m1, m2, 0.95);
                std::cout << "bounce\n";
            }
            else {
                bounce1D(v1.y, v2.y, m1, m2, 0.95);
            }

            position = p1;
            compare->set_pos(p2);

            velocity = v1;
            compare->set_vel(v2);//applies velocity
        }
    }
}

void rectcollide::update(Vector2 mousepos, bool pressed, bool released) {
    if (pinrect(mousepos, position, size) && !held && pressed) {
        held = true;
    }
    if (held && released) {
        held = false;
        velocity = Vector2ClampValue(velocity, 0, maxspeed);
    }

    rigidbody::update(mousepos);

    wallbounce(0, 1000, 0, 1000, position, velocity, size.x / 2, size.y / 2);
}

void rectcollide::draw() {
    DrawRectangle(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y, BLACK);
    DrawRectangle(position.x - size.x / 2 + 5, position.y - size.y / 2 + 5, size.x - 10, size.y - 10, DARKBLUE);
}

Vector2 rectcollide::get_corner() {
    Vector2 cornerpos;
    cornerpos.x = position.x - size.x / 2;
    cornerpos.y = position.y - size.y / 2;
    return cornerpos;
}

void rectcollide::set_vel(Vector2 v) {
    velocity = v;
}