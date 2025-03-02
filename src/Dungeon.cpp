#include "Dungeon.h"

#define TILE_SIZE 16

Dungeon::Dungeon(int width, int height) : width(width), height(height), tiles(width * height, NONE)
{
	wallTexture = LoadTexture("res/wall.png");
	playerTexture = LoadTexture("res/player.png");
}

void Dungeon::Generate()
{
	std::fill(tiles.begin(), tiles.end(), NONE);

	int x = width / 2;
	int y = height / 2;
	tiles[y * width + x] = FLOOR;

	int lastDirection = -1;

	//Modified drunk walk
	for (int i = 0; i < 1500; i++)
	{
		int randomDirection;
		do {
			randomDirection = GetRandomValue(0, 3);
		} while (randomDirection == lastDirection);

		if (randomDirection == 0) { y--; }		//Up
		else if (randomDirection == 1) { y++; } //Down
		else if (randomDirection == 2) { x--; } //Left
		else if (randomDirection == 3) { x++; } //Right

		if (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1)
		{
			x = width / 2;
			y = height / 2;
			lastDirection = -1;
		}
		else
		{
			lastDirection = randomDirection;
		}

		tiles[y * width + x] = FLOOR;
	}

	//Surround floor with walls
	int maxTiles = width * height;
	for (int i = 0; i < maxTiles; i++)
	{
		if (tiles[i] == FLOOR)
		{
			int x = i % width;
			int y = i / width;

			if (tiles[(y - 1) * width + x] != FLOOR)
				tiles[(y - 1) * width + x] = WALL;

			if (tiles[(y + 1) * width + x] != FLOOR)
				tiles[(y + 1) * width + x] = WALL;

			if (tiles[y * width + (x - 1)] != FLOOR)
				tiles[y * width + (x - 1)] = WALL;

			if (tiles[y * width + (x + 1)] != FLOOR)
				tiles[y * width + (x + 1)] = WALL;

			if (tiles[(y - 1) * width + (x - 1)] != FLOOR)
				tiles[(y - 1) * width + (x - 1)] = WALL;

			if (tiles[(y + 1) * width + (x + 1)] != FLOOR)
				tiles[(y + 1) * width + (x + 1)] = WALL;

			if (tiles[(y - 1) * width + (x + 1)] != FLOOR)
				tiles[(y - 1) * width + (x + 1)] = WALL;

			if (tiles[(y + 1) * width + (x - 1)] != FLOOR)
				tiles[(y + 1) * width + (x - 1)] = WALL;
		}
	}
}

void Dungeon::Draw()
{
	int maxTiles = width * height;
	for (int i = 0; i < maxTiles; i++)
	{
		int tileX = i % width;
		int tileY = i / width;
		int worldX = tileX * TILE_SIZE;
		int worldY = tileY * TILE_SIZE;

		if (tiles[i] == WALL)
		{
			DrawTexture(wallTexture, worldX, worldY, LIGHTGRAY);
		}
	}
	DrawTexture(playerTexture, (width / 2) * TILE_SIZE, (height / 2) * TILE_SIZE, WHITE);
}
