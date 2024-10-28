#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <iostream>


bool pincircle(Vector2 ppos, Vector2 cpos, float radius) {// determines if a point is inside a circle
    float xdif = ppos.x - cpos.x;
    float ydif = ppos.y - cpos.y;
    float tdif = sqrt(xdif * xdif + ydif * ydif);//distance between points
    if (tdif < radius) {
        return true;
    }
    
    return false;
}

bool pinrect(Vector2 ppos, Vector2 cpos, Vector2 size) {// determines if a point is inside a rectangle
    float xdif = ppos.x - cpos.x;
    float ydif = ppos.y - cpos.y;
    if (-size.x / 2 < xdif and xdif < size.x / 2 and -size.y / 2 < ydif and ydif < size.y / 2) {
        return true;
    }
    return false;
}

bool rectoverlap(Vector2 pos1, Vector2 pos2, Vector2 size1, Vector2 size2) {// determines if a point is inside a rectangle
    float xdif = pos1.x - pos2.x;
    float ydif = pos1.y - pos2.y;
    if (-(size1.x + size2.x) / 2 < xdif and xdif < (size1.x + size2.x) / 2 and -(size1.y + size2.y) / 2 < ydif and ydif < (size1.y + size2.y) / 2) {
        return true;
    }
    return false;
}

bool circleoverlap(Vector2 pos1, Vector2 pos2, float rad1, float rad2) {
    if (Vector2Distance(pos1, pos2) < rad1 + rad2) {
        return true;
    }
    return false;
}

void resolvecirclecollision(Vector2& pos1, Vector2& pos2, float r1, float r2, float m1, float m2, Vector2 v1, Vector2 v2) {//move circles outside eachother
    float xdif = pos1.x - pos2.x;
    float ydif = pos1.y - pos2.y;

    if (xdif == 0) {
        xdif = 0.001;
    }
    if (ydif == 0) {
        ydif = 0.001;
    }

    float tdif = sqrt(xdif * xdif + ydif * ydif);//distance between points

    xdif /= tdif;
    ydif /= tdif;//normalised

    float rt = r1 + r2;

    float tomovetotal = rt - tdif;

    float tomove1 = (m2 * tomovetotal) / (m1 + m2);
    float tomove2 = (m1 * tomovetotal) / (m1 + m2);

    pos1.x += xdif * tomove1;
    pos1.y += ydif * tomove1;
    pos2.x -= xdif * tomove2;
    pos2.y -= ydif * tomove2;
}

void bounce1D(float& vel1, float& vel2, float m1, float m2, float restitution) {
    float v1 = (restitution * m2 * (vel2 - vel1) + m1 * vel1 + m2 * vel2) / (m1 + m2);
    float v2 = (restitution * m1 * (vel1 - vel2) + m2 * vel2 + m1 * vel1) / (m2 + m1);//final velocity calculations for 1D inelastic collisions

    vel1 = v1;
    vel2 = v2;
}

void bounce2D(Vector2& vel1, Vector2& vel2, float m1, float m2, float angle, float restitution) {
    Vector2 rotatedv1 = Vector2Rotate(vel1, angle);
    Vector2 rotatedv2 = Vector2Rotate(vel2, angle);//rotates points so x axis is normal to makle calculations easier

    bounce1D(rotatedv1.y, rotatedv2.y, m1, m2, restitution);

    vel1 = Vector2Rotate(rotatedv1, -angle);
    vel2 = Vector2Rotate(rotatedv2, -angle);//return updated velocities
}

void wallbounce(int lowx, int highx, int lowy, int highy, Vector2& pos, Vector2& vel, float xdistance, float ydistance, bool& g) {
    //takes an object size xdistance by ydistance and reflects velocity if outside x/y bounds

    float res = 0.90;

    if (pos.x >= highx - xdistance) {
        vel.x = -abs(vel.x * res);
        pos.x = highx - xdistance;
        g = true;
    }
    else if (pos.x <= lowx + xdistance) {
        vel.x = abs(vel.x * res);
        pos.x = lowx + xdistance;
        g = true;
    }
    if (pos.y >= highy - ydistance) {
        vel.y = -abs(vel.y * res);
        pos.y = highy - ydistance;
        g = true;
    }
    else if (pos.y <= lowy + ydistance) {
        vel.y = abs(vel.y * res);
        pos.y = lowy + ydistance;
        g = true;
    }
}

