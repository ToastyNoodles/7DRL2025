#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>

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
private:
	std::vector<int> GetFloorIndices();
	std::vector<int> GetFloorIndicesExcludingPlayerRadius(int radius);

	void SpawnExit();
	void SpawnPlayer();

	std::vector<Tile> tiles;
	std::vector<Entity*> entities;
	int width, height;

	Texture wallTexture;
	Texture exitTexture;
};