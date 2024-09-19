#include "include/rectcollide.h"

/* FOR LATER
class rectcollider { //class for rect rigidbody
    float sizex;
    float sizey;
    float mass;
    Vector2 position;
    Vector2 velocity;
    bool held = false;

public:
    rectcollider() {
        sizex = 0;
        sizey = 0;
        mass = 0;
        position.x = 0;
        position.y = 0;
        velocity.x = 0;
        velocity.y = 0;
    }
    rectcollider(float xsize, float ysize, float xpos, float ypos, float m = 1, float xvel = 0, float yvel = 0) {
        sizex = xsize;
        sizey = ysize;
        mass = xsize * ysize * m;
        position.x = xpos;
        position.y = ypos;
        velocity.x = xvel;
        velocity.y = yvel;
    }

    void clicked(Vector2 mousepos) {
        Vector2 dif = Vector2Subtract(mousepos, position);
        velocity = dif;
    }

    void update(Vector2 mousepos, bool press, bool release) {
        if (press) {
            if (pinrect(mousepos, get_corner(), Vector2{ sizex, sizey })) {
                held = true;
            }
        }
        if (release) {
            held = false;
        }
        if (held) {
            clicked(mousepos);
        }
        wallbounce(000, 1000, 00, 1000, position, velocity, sizex / 2, sizey / 2);
        position = Vector2Add(position, velocity);
    }

    void draw() {
        DrawRectangle(position.x - sizex / 2, position.y - sizey / 2, sizex, sizey, BLACK);
    }

    float get_xsize() {
        return sizex;
    }
    float get_ysize() {
        return sizey;
    }
    Vector2 get_vel() {
        return velocity;
    }
    Vector2 get_pos() {
        return position;
    }
    Vector2 get_corner() {
        Vector2 cornerpos;
        cornerpos.x = position.x - sizex / 2;
        cornerpos.y = position.y - sizey / 2;
        return cornerpos;
    }
    void set_vel(Vector2 v) {
        velocity = v;
    }
};
*/