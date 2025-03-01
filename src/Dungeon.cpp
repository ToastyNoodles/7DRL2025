#include "Dungeon.h"

Dungeon::Dungeon()
{
	wallTexture = LoadTexture("res/wall.png");
}

void Dungeon::GenerateDungeon()
{
	//Initialize dungeon map 
	for (int i = 0; i < DUNGEON_COUNT; i++)
	{
		dungeon[i] = WALL;
	}

	//Spawn drunkWalker
	Entity drunkWalker = { *this, Walker };
	drunkWalker.position = { floorf(DUNGEON_WIDTH / 2.0f), floorf(DUNGEON_HEIGHT / 2.0f) };
	drunkWalker.healthPoints = 1000;
	drunkWalker.Walk();
}

void Dungeon::DrawDungeon()
{
	//Draw whatever texture is at the position
	for (int i = 0; i < DUNGEON_COUNT; i++)
	{
		if (dungeon[i] != FLOOR)
		{
			Vector2 tilePosition = PositionFromIndex(i);
			DrawTextureV(wallTexture, Vector2Multiply(tilePosition, { TILE_SIZE, TILE_SIZE }), WHITE);
		}
	}
}

void Dungeon::SetTile(Vector2 position, Tile tile)
{
	dungeon[IndexFromPosition(position)] = tile;
}

Vector2 Dungeon::PositionFromIndex(int index)
{
	return { floorf(index % DUNGEON_WIDTH), floorf(index / DUNGEON_WIDTH) };
}

int Dungeon::IndexFromPosition(Vector2 position)
{
	return floorf(position.y) * DUNGEON_WIDTH + floorf(position.x);
}
