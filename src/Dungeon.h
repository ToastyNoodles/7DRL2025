#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>

enum Tile
{
	NONE = 0,
	FLOOR = 1,
	WALL = 2
};

class Dungeon
{
public:
	Dungeon(int width, int height);
	void Generate();
	void Draw();
private:
	std::vector<Tile> tiles;
	int width, height;

	Texture wallTexture;
	Texture playerTexture;
};