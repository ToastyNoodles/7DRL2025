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
	EXIT = 3,
	PLAYER = 4,
	ENEMY = 5
};

class Dungeon
{
public:
	Dungeon(int width, int height);
	void Generate();
	void Update();
	void Draw();

	Vector2 GetPlayerPosition();
	bool IsTileValid(int x, int y);
	void SetPlayerTurn(bool state);
	void SetTile(int x, int y, Tile type);
	Tile GetTile(int x, int y);

	int currentFloor;
private:
	std::vector<int> GetFloorIndices();
	std::vector<int> GetFloorIndicesExcludingPlayerRadius(int radius);

	void SpawnExit();
	void SpawnPlayer();
	void SpawnEnemies();

	std::vector<Tile> tiles;
	std::vector<Entity*> entities;
	Entity* player;
	int width, height;
	bool isPlayerTurn;

	Texture wallTexture;
	Texture exitTexture;
};