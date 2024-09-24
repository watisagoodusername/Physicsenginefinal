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

    rectcollide finishcreationr(Vector2 mousepos) {//creates a rectangle collider
        end = mousepos;
        active = false;

        Vector2 s = size();

        if (start.x < end.x) { centre.x = start.x + s.x / 2; }
        else { centre.x = end.x + s.x / 2; }
        if (start.y < end.y) { centre.y = start.y + s.y / 2; }
        else { centre.y = end.y + s.y / 2; }

        return rectcollide(s.x, s.y, centre.x, centre.y);
    }

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

int main() {

    int screenwidth = 1000;
    int screenheight = 1000;
    InitWindow(screenwidth, screenheight, "physics");

    SetTargetFPS(60);

    createobject ct("ball");

    std::vector<ballcollide> balls = { ballcollide(20, 50, 50, 1, 5, 4) };
    std::vector<rectcollide> boxes = { rectcollide(20, 20, 500, 500, 1, -2, 3) };
    balls.shrink_to_fit();
    boxes.shrink_to_fit();
    int ballcount = balls.size();
    int boxcount = boxes.size();

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
                    balls.push_back(ct.finishcreationb(mousepos));
                    ballcount = balls.size();
                }
                else if (ct.objecttype == "rect") {
                    boxes.push_back(ct.finishcreationr(mousepos));
                    boxcount = boxes.size();
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
                balls.push_back(ballcollide(GetRandomValue(3, 14), GetRandomValue(10, 990), GetRandomValue(10, 990)));
            }
            for (int i = 0; i < 200; i++) {
                balls.push_back(ballcollide(GetRandomValue(14, 34), GetRandomValue(10, 990), GetRandomValue(10, 990)));
            }
            for (int i = 0; i < 5; i++) {
                balls.push_back(ballcollide(GetRandomValue(34, 70), GetRandomValue(10, 990), GetRandomValue(10, 990)));
            }
            ballcount = balls.size();
        }
        if (IsKeyPressed(KEY_B)) {
            for (int i = 0; i < 1500; i++) {
                balls.push_back(ballcollide(GetRandomValue(8, 12), GetRandomValue(10, 990), GetRandomValue(10, 990)));
            }
            ballcount = balls.size();
        }
        if (IsKeyPressed(KEY_W)) {
            balls.push_back(ballcollide(GetRandomValue(8, 12), 850, 930, 1750, GetRandomValue(-5, -1), GetRandomValue(-5, -1)));
            ballcount = balls.size();
        }
        if (IsKeyPressed(KEY_C)) {
            balls.clear();
            boxes.clear();
            balls.shrink_to_fit();
            boxes.shrink_to_fit();
            ballcount = balls.size();
            boxcount = boxes.size();
        }

        for (int i = 0; i < ballcount; i++) {//update every rigidbody
            balls.at(i).update(mousepos, IsMouseButtonPressed(0), IsMouseButtonReleased(0));
        }
        for (int i = 0; i < boxcount; i++) {//update every rigidbody
            boxes.at(i).update(mousepos, IsMouseButtonPressed(0), IsMouseButtonReleased(0));
        }

        for (int i = 0; i < ballcount - 1; i++) {//updates velocities
            ballcollide* current = &balls.at(i);
            for (int j = i + 1; j < balls.size(); j++) {
                ballcollide* compare = &balls.at(j);

                current->ballcollision(compare);
            }
        }

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            ct.draw(mousepos);

            for (int i = 0; i < ballcount; i++) {
                balls.at(i).draw();
            }
            for (int i = 0; i < boxcount; i++) {
                boxes.at(i).draw();
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
