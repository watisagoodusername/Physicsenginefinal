#include <iostream>
#include <raylib.h>
#include <vector>
#include "include/PhysicsFunctions.h"
#include "include/rigidbody.h"
#include "include/ballcollide.h"
#include "include/rectcollide.h"
#include "include/createobject.h"
#include "include/camera.h"

int main() {

    int screenwidth = 1000;
    int screenheight = 1000;
    InitWindow(screenwidth, screenheight, "physics");

    SetTargetFPS(60);

    createobject ct("ball");

    camera cam(Vector2 {500, 500}, 1);

    std::vector<ballcollide> balls = { ballcollide(20, 50, 50, 1, 5, 4) };
    std::vector<rectcollide> boxes = { rectcollide(20, 20, 500, 500, 1, -2, 3) };
    balls.shrink_to_fit();
    boxes.shrink_to_fit();
    int ballcount = balls.size();
    int boxcount = boxes.size();

    Vector2 gravity = Vector2{ 0, 1 };

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

        Vector2 mousepos = cam.camtoworldspace(GetMousePosition());

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
            for (int i = 0; i < 457; i++) {
                balls.push_back(ballcollide(GetRandomValue(11, 13), GetRandomValue(10, 990), GetRandomValue(10, 990)));
            }
            ballcount = balls.size();
        }
        if (IsKeyPressed(KEY_S)) {
            for (int i = 0; i < 457; i++) {
                boxes.push_back(rectcollide(GetRandomValue(25, 28), GetRandomValue(25, 28), GetRandomValue(10, 990), GetRandomValue(10, 990)));
            }
            boxcount = boxes.size();
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

        if (IsKeyDown(KEY_UP)) { cam.changepos(Vector2{ 0, -5 }); }

        if (IsKeyDown(KEY_DOWN)) { cam.changepos(Vector2{ 0, 5 }); }

        if (IsKeyDown(KEY_LEFT)) { cam.changepos(Vector2{ -5, 0 }); }

        if (IsKeyDown(KEY_RIGHT)) { cam.changepos(Vector2{ 5, 0 }); }

        int scroll = GetMouseWheelMove();
        if (scroll != 0) { cam.changezoom(pow(1.1, scroll)); }

        //COLLISION TESTS ---------------------------------------------
        for (int i = 20; i > 0; i--) { // updates 80 times a frame
            for (int i = 0; i < ballcount - 1; i++) {//updates velocities
                ballcollide* current = &balls.at(i);
                for (int j = i + 1; j < balls.size(); j++) {
                    ballcollide* compare = &balls.at(j);

                    current->ballcollision(compare, gravity);
                }
            }
            for (int i = 0; i < boxcount - 1; i++) {//updates velocities
                rectcollide* current = &boxes.at(i);
                for (int j = i + 1; j < boxcount; j++) {
                    rectcollide* compare = &boxes.at(j);

                    current->rectcollision(compare);
                }
            }
            for (int i = 0; i < boxcount; i++) {//updates velocities
                rectcollide* current = &boxes.at(i);
                for (int j = 0; j < ballcount; j++) {
                    ballcollide* compare = &balls.at(j);

                    current->rectballcollision(compare);
                }
            }
        }
        //UPDATING --------------------------------------------

        for (int i = 0; i < ballcount; i++) {//update every rigidbody
            balls.at(i).update(gravity, mousepos, IsMouseButtonPressed(0), IsMouseButtonReleased(0));
        }
        for (int i = 0; i < boxcount; i++) {//update every rigidbody
            boxes.at(i).update(gravity, mousepos, IsMouseButtonPressed(0), IsMouseButtonReleased(0));
        }

        BeginDrawing();

            Vector2 zz = cam.worldtocamspace(Vector2{ 0, 0 });
            Vector2 zo = cam.worldtocamspace(Vector2{ 0, 1000 });
            Vector2 oz = cam.worldtocamspace(Vector2{ 1000, 0 });
            Vector2 oo = cam.worldtocamspace(Vector2{ 1000, 1000 });

            ClearBackground(BLACK);

            DrawRectangle(zz.x, zz.y, cam.rescale(screenwidth), cam.rescale(screenheight), LIGHTGRAY);

            ct.draw(mousepos, cam);

            for (int i = 0; i < ballcount; i++) {
                balls.at(i).draw(cam);
            }
            for (int i = 0; i < boxcount; i++) {
                boxes.at(i).draw(cam);
            }

            DrawText(TextFormat("%f", dt), 3, 3, 20, WHITE);
            DrawText(TextFormat("%i", fps), 950, 3, 20, WHITE);

            DrawLine(490, 500, 510, 500, BLACK);
            DrawLine(500, 490, 500, 510, BLACK);

            DrawLine(zz.x, zz.y, zo.x, zo.y, BLACK);
            DrawLine(zo.x, zo.y, oo.x, oo.y, BLACK);
            DrawLine(oo.x, oo.y, oz.x, oz.y, BLACK);
            DrawLine(oz.x, oz.y, zz.x, zz.y, BLACK);

            DrawTextureEx(wizard, cam.worldtocamspace(Vector2{ (float)screenwidth - wizard.width, (float)screenheight - wizard.width }), 0, cam.rescale(1), WHITE);
            DrawTextureEx(wizard, cam.worldtocamspace(Vector2{ (float)screenwidth - wizard.width, (float)screenheight - wizard.width }), 0, cam.rescale(1), WHITE);

        EndDrawing();
    }

    UnloadTexture(wizard);
    UnloadTexture(wizardshadow);

    CloseWindow();

    return 0;
}
