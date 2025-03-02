#include "raylib.h"
#include "raymath.h"
#include "Dungeon.h"
#include <iostream>

int main()
{
    SetWindowState(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280, 720, "7DRL");
	SetTargetFPS(144); 
    
    Dungeon dungeon = { 100, 100 };

    Camera2D camera = {};
    camera.zoom = 2.0f;

	while (!WindowShouldClose())
	{
        camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        camera.zoom += GetMouseWheelMove() * (0.1 * camera.zoom);

        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        {
            Vector2 mouseDelta = Vector2Divide(GetMouseDelta(), { camera.zoom, camera.zoom });
            camera.target = { camera.target.x - mouseDelta.x, camera.target.y - mouseDelta.y };
        }

        if (IsKeyPressed(KEY_R))
        {
            dungeon.Generate();
        }

        dungeon.Update();

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        dungeon.Draw();
        EndMode2D();


        EndDrawing();
	}
}