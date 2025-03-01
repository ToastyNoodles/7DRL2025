#include "raylib.h"
#include "raymath.h"
#include "Dungeon.h"

int main()
{
	InitWindow(1280, 720, "7DRL");
	SetTargetFPS(60); 
    
    Camera2D camera = {};
    camera.zoom = 2.0f;

	Dungeon dungeon;
	dungeon.GenerateDungeon();

	while (!WindowShouldClose())
	{
        camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        camera.zoom += GetMouseWheelMove() * (0.1 * camera.zoom);

        if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON))
        {
            Vector2 mouseDelta = Vector2Divide(GetMouseDelta(), { camera.zoom, camera.zoom });
            camera.target = { camera.target.x - mouseDelta.x, camera.target.y - mouseDelta.y };
        }

        if (IsKeyPressed(KEY_R))
        {
            dungeon.GenerateDungeon();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        dungeon.DrawDungeon();
        EndMode2D();


        EndDrawing();
	}
}