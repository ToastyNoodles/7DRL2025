#include "raylib.h"
#include "raymath.h"
#include "Dungeon.h"
#include <iostream>

int main()
{
	InitWindow(1280, 720, "7DRL");
	SetTargetFPS(60); 
    
	Dungeon dungeon;
	dungeon.GenerateDungeon();

    Camera2D camera = {};
    camera.zoom = 1.0f;
    camera.target = Vector2Multiply(dungeon.GetPlayerPosition(), { TILE_SIZE, TILE_SIZE });

	while (!WindowShouldClose())
	{
        camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        camera.target = Vector2Lerp(camera.target, Vector2Multiply(dungeon.GetPlayerPosition(), { TILE_SIZE, TILE_SIZE }), GetFrameTime() * 4.0f);

        if (IsKeyPressed(KEY_R))
        {
            dungeon.GenerateDungeon();
        }

        dungeon.UpdateDungeon();

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        dungeon.DrawDungeon();
        EndMode2D();


        EndDrawing();
	}
}