#include <raymath.h>

bool pincircle(Vector2 ppos, Vector2 cpos, float radius);

bool pinrect(Vector2 ppos, Vector2 cpos, Vector2 size);

bool rectoverlap(Vector2 pos1, Vector2 pos2, Vector2 size1, Vector2 size2);

bool circleoverlap(Vector2 pos1, Vector2 pos2, float rad1, float rad2);

void resolvecirclecollision(Vector2& pos1, Vector2& pos2, float r1, float r2, float m1, float m2, Vector2 v1, Vector2 v2);

void resolverectcollision(Vector2& pos1, Vector2& pos2, Vector2 size1, Vector2 size2, float m1, float m2, Vector2 v1, Vector2 v2);

void bounce1D(float& vel1, float& vel2, float m1, float m2, float restitution);

void bounce2D(Vector2& vel1, Vector2& vel2, float m1, float m2, float angle, float restitution);

void wallbounce(int lowx, int highx, int lowy, int highy, Vector2& pos, Vector2& vel, float xdistance, float ydistance, bool& g);
