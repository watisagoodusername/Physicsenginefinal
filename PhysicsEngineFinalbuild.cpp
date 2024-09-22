#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "include/PhysicsFunctions.h"
#include "include/rigidbody.h"
#include "include/ballcollide.h"
#include "include/rectcollide.h"

class createobject {//contains information about object to be created 
    Vector2 start;
    Vector2 end;
    Vector2 centre;

    Vector2 size() {
        Vector2 s;
        s.x = abs(start.x - end.x);
        s.y = abs(start.y - end.y);
        return s;
    }

public:
    bool active;
    std::string objecttype;
    createobject(std::string otype) {
        objecttype = otype;
        start.x = 0;
        start.y = 0;
        end.x = 0;
        end.y = 0;
        centre.x = 0;
        centre.y = 0;
        active = false;
    }

    float radius() {
        return abs(start.x - end.x) / 2;
    }

    void initcreation(Vector2 mousepos) {
        start = mousepos;
        active = true;
    }
    ballcollide finishcreationb(Vector2 mousepos) {//creates a ball collider
        end = mousepos;
        active = false;

        Vector2 s = size();

        if (start.x < end.x) { centre.x = start.x + s.x / 2; }
        else { centre.x = end.x + s.x / 2; }
        if (start.y < end.y) { centre.y = start.y + s.y / 2; }
        else { centre.y = end.y + s.y / 2; }

        return ballcollide(radius(), centre.x, centre.y);
    }
    /*rectcollider finishcreationr(Vector2 mousepos) {//creates a rectangle collider
        end = mousepos;
        active = false;

        Vector2 s = size();

        if (start.x < end.x) { centre.x = start.x + s.x / 2; }
        else { centre.x = end.x + s.x / 2; }
        if (start.y < end.y) { centre.y = start.y + s.y / 2; }
        else { centre.y = end.y + s.y / 2; }

        return rectcollider(s.x, s.y, centre.x, centre.y);
    }*/
    void draw(Vector2 mousepos) {
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

    Vector2 get_start() {
        return start;
    }
    Vector2 get_centre(Vector2 mousepos) {//center position for circle creation
        end = mousepos;

        Vector2 s = size();

        if (start.x < end.x) { centre.x = start.x + s.x / 2; }
        else { centre.x = end.x + s.x / 2; }
        if (start.y < end.y) { centre.y = start.y + s.y / 2; }
        else { centre.y = end.y + s.y / 2; }

        return centre;
    }
    std::string get_object() {
        return objecttype;
    }
};

static void circlecollide(ballcollide* current, ballcollide* compare) {
    Vector2 p1 = current->get_pos();
    Vector2 p2 = compare->get_pos();// position values

    float r1 = current->get_r();
    float r2 = compare->get_r();

    if (circleoverlap(p1, p2, r1, r2)) {
        Vector2 dif = Vector2Subtract(p1, p2);// distance between circles

        float angle = atan2(dif.x, dif.y);

        Vector2 v1 = current->get_vel();
        Vector2 v2 = compare->get_vel(); //velocity values, passed by value

        float m1 = current->get_m();
        float m2 = compare->get_m();// mass

        bounce(v1, v2, m1, m2, angle, 0.95);//velocity calculations
        resolvecirclecollision(p1, p2, r1, r2, m1, m2);//changes p1 and p2 so they arent inside each other

        current->set_pos(p1);
        compare->set_pos(p2);//applies position

        current->set_vel(v1);
        compare->set_vel(v2);//applies velocity
    }
}

int main() {

    int screenwidth = 1000;
    int screenheight = 1000;
    InitWindow(screenwidth, screenheight, "physics");

    SetTargetFPS(60);

    createobject ct("ball");

    std::vector<ballcollide> bodies = { ballcollide(20, 50, 50, 1, 5, 4) };
    bodies.shrink_to_fit();

    Image wizardimg = LoadImage("Resources/Wizardofphysics.png"); // Loaded in CPU memory (RAM)
    Image wizardimg2 = LoadImage("Resources/Wizardofphysics.png");

    ImageResizeNN(&wizardimg, 160, 160);
    ImageResize(&wizardimg2, 170, 170);

    Texture2D wizard = LoadTextureFromImage(wizardimg);// Image converted to texture, GPU memory (VRAM)
    Texture2D wizardshadow = LoadTextureFromImage(wizardimg2);

    UnloadImage(wizardimg);
    UnloadImage(wizardimg2);

    bool game = true;
    while (game)
    {
        float dt = GetFrameTime();
        int fps = GetFPS();

        if (WindowShouldClose()) {
            game = false;
        }

        Vector2 mousepos = GetMousePosition();

        bool mousedown = false;
        if (IsMouseButtonDown(0)) {
            mousedown = true;
        }
        if (IsMouseButtonPressed(1)) {
            if (!ct.active) {
                ct.initcreation(mousepos);
            }
        }
        if (IsMouseButtonReleased(1)) {
            if (ct.active) {
                if (ct.objecttype == "ball") {
                    bodies.push_back(ct.finishcreationb(mousepos));
                }
            }
        }
        if (IsMouseButtonPressed(2)) {
            if (ct.objecttype == "ball") {
                ct.objecttype = "rect";
            }
            else {
                ct.objecttype = "ball";
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            for (int i = 0; i < 795; i++) {
                bodies.push_back(ballcollide(GetRandomValue(3, 14), GetRandomValue(10, 990), GetRandomValue(10, 990)));
            }
            for (int i = 0; i < 200; i++) {
                bodies.push_back(ballcollide(GetRandomValue(14, 34), GetRandomValue(10, 990), GetRandomValue(10, 990)));
            }
            for (int i = 0; i < 5; i++) {
                bodies.push_back(ballcollide(GetRandomValue(34, 70), GetRandomValue(10, 990), GetRandomValue(10, 990)));
            }
        }
        if (IsKeyPressed(KEY_B)) {
            for (int i = 0; i < 1500; i++) {
                bodies.push_back(ballcollide(GetRandomValue(8, 12), GetRandomValue(10, 990), GetRandomValue(10, 990)));
            }
        }
        if (IsKeyPressed(KEY_W)) {
            bodies.push_back(ballcollide(GetRandomValue(8, 12), 850, 930, 1750, GetRandomValue(-5, -1), GetRandomValue(-5, -1)));
        }
        if (IsKeyPressed(KEY_C)) {
            bodies.clear();
            bodies.shrink_to_fit();
        }

        size_t bodycount = bodies.size();

        for (int i = 0; i < bodycount; i++) {//update every rigidbody
            bodies.at(i).update(mousepos, IsMouseButtonPressed(0), IsMouseButtonReleased(0));
        }

        //for (int a = 0; a < 2; a++) {
            for (int i = 0; i < bodycount; i++) {//updates velocities
                ballcollide* current = &bodies.at(i);
                if (bodies.size() >= i) {
                    for (int j = i + 1; j < bodycount; j++) {
                        ballcollide* compare = &bodies.at(j);

                        current->ballcollision(compare);
                        //circlecollide(current, compare);
                    }
                }
            }
        //}

        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        ct.draw(mousepos);

        for (int i = 0; i < bodycount; i++) {
            bodies.at(i).draw();
        }

        DrawText(TextFormat("%f", dt), 3, 3, 20, WHITE);
        DrawText(TextFormat("%i", fps), 950, 3, 20, WHITE);

        DrawTexture(wizardshadow, screenwidth - wizard.width, screenheight - wizard.height, CLITERAL(Color){ 0, 0, 0, 64 });
        DrawTexture(wizard, screenwidth - wizard.width, screenheight - wizard.height, WHITE);

        EndDrawing();
    }

    UnloadTexture(wizard);
    UnloadTexture(wizardshadow);

    CloseWindow();

    return 0;
}
