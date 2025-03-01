#include "Dungeon.h"

Dungeon::Dungeon()
{
	playerTexture = LoadTexture("res/player.png");
	wallTexture = LoadTexture("res/wall.png");
}

void Dungeon::GenerateDungeon()
{
	entities.clear();

	//Initialize dungeon map 
	for (int i = 0; i < DUNGEON_COUNT; i++)
	{
		dungeon[i] = WALL;
	}

	//Spawn drunkWalker
	Vector2 dungeonCenter = { floorf(DUNGEON_WIDTH / 2.0f), floorf(DUNGEON_HEIGHT / 2.0f) };

	Entity drunkWalker = { *this, Walker };
	drunkWalker.position = dungeonCenter;
	drunkWalker.healthPoints = 1000;
	drunkWalker.Walk();

	//Spawn player
	entities.emplace_back(*this, Player);
	player = &entities[0];
	player->position = dungeonCenter;
	player->texture = playerTexture;
	player->healthPoints = 20;
	player->actionPoints = 5;
}

void Dungeon::UpdateDungeon()
{
	if (IsKeyPressed(KEY_W))
	{
		player->Move({ 0, -1 });
	}
	else if (IsKeyPressed(KEY_S))
	{
		player->Move({ 0, 1 });
	}
	else if (IsKeyPressed(KEY_A))
	{
		player->Move({ -1, 0 });
	}
	else if (IsKeyPressed(KEY_D))
	{
		player->Move({ 1, 0 });
	}
}

void Dungeon::DrawDungeon()
{
	//Draw whatever texture is at the position
	for (int i = 0; i < DUNGEON_COUNT; i++)
	{
		if (dungeon[i] != FLOOR)
		{
			Vector2 tilePosition = PositionFromIndex(i);
			DrawTextureV(wallTexture, Vector2Multiply(tilePosition, { TILE_SIZE, TILE_SIZE }), LIGHTGRAY);
		}
	}

	for (Entity& ent : entities)
	{
		ent.Draw();
	}
}

void Dungeon::SetTile(Vector2 position, Tile tile)
{
	dungeon[IndexFromPosition(position)] = tile;
}

Tile Dungeon::GetTile(Vector2 position)
{
	return dungeon[IndexFromPosition(position)];
}

Vector2 Dungeon::GetPlayerPosition()
{
	return player->position;
}

Vector2 Dungeon::PositionFromIndex(int index)
{
	return { floorf(index % DUNGEON_WIDTH), floorf(index / DUNGEON_WIDTH) };
}

int Dungeon::IndexFromPosition(Vector2 position)
{
	return floorf(position.y) * DUNGEON_WIDTH + floorf(position.x);
}
