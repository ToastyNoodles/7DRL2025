#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Entity.h"
#include <vector>

#define DUNGEON_WIDTH 64
#define DUNGEON_HEIGHT 64
#define DUNGEON_COUNT DUNGEON_WIDTH * DUNGEON_HEIGHT
#define TILE_SIZE 16

enum Tile
{
	NONE = 0,
	WALL = 1,
	FLOOR = 2
};

class Dungeon
{
public:
	Dungeon();
	void GenerateDungeon();
	void UpdateDungeon();
	void DrawDungeon();
	void SetTile(Vector2 position, Tile tile);
	Tile GetTile(Vector2 position);
	Vector2 GetPlayerPosition();
	Vector2 PositionFromIndex(int index);
	int IndexFromPosition(Vector2 position);
private:
	Tile dungeon[DUNGEON_COUNT];
	std::vector<Entity> entities;
	Entity* player;

	Texture playerTexture;
	Texture wallTexture;
};