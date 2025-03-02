#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>

#define TILE_SIZE 16

class Entity;

enum Tile
{
	NONE = 0,
	FLOOR = 1,
	WALL = 2,
	EXIT
};

class Dungeon
{
public:
	Dungeon(int width, int height);
	void Generate();
	void Update();
	void Draw();

	bool IsTileValid(int x, int y);
	void SetPlayerTurn(bool state);
private:
	std::vector<int> GetFloorIndices();
	std::vector<int> GetFloorIndicesExcludingPlayerRadius(int radius);

	void SpawnExit();
	void SpawnPlayer();
	void SpawnEnemies(int count);

	std::vector<Tile> tiles;
	std::vector<Entity*> entities;
	Entity* player;
	int width, height;
	bool isPlayerTurn;

	Texture wallTexture;
	Texture exitTexture;
};