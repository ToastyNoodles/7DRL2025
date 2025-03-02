#pragma once
#include "Dungeon.h"

struct Entity
{
	int x, y;
	bool isActive;
	Texture texture;
	virtual void Draw() = 0;
	virtual void Update(Dungeon& dungeon) = 0;
};

struct Player : public Entity
{
	Player(int spawnX, int spawnY, Texture playerTexture)
	{
		x = spawnX;
		y = spawnY;
		isActive = true;
		texture = playerTexture;
	}

	void Draw() override
	{
		int worldX = x * TILE_SIZE;
		int worldY = y * TILE_SIZE;
		DrawTexture(texture, worldX, worldY, WHITE);
	}

	void Update(Dungeon& dungeon) override
	{
		bool moved = false;
		int nextX = x, nextY = y;

		if (IsKeyPressed(KEY_W)) { nextY -= 1; moved = true; }
		else if (IsKeyPressed(KEY_S)) { nextY += 1; moved = true; }
		else if (IsKeyPressed(KEY_A)) { nextX -= 1; moved = true; }
		else if (IsKeyPressed(KEY_D)) { nextX += 1; moved = true; }

		if (dungeon.IsTileValid(nextX, nextY) && moved)
		{
			x = nextX;
			y = nextY;
			dungeon.SetPlayerTurn(false);
		}
	}
};

struct Enemy : public Entity
{
	Enemy(int spawnX, int spawnY, Texture enemyTexture)
	{
		x = spawnX;
		y = spawnY;
		isActive = true;
		texture = enemyTexture;
	}

	void Draw() override
	{
		int worldX = x * TILE_SIZE;
		int worldY = y * TILE_SIZE;
		DrawTexture(texture, worldX, worldY, RED);
	}

	void Update(Dungeon& dungeon) override
	{
		int nextX = x, nextY = y;
		bool moveHorizontally = GetRandomValue(0, 1);

		if (moveHorizontally) 
		{
			nextX = x + GetRandomValue(-1, 1);
		}
		else 
		{
			nextY = y + GetRandomValue(-1, 1);
		}

		if (dungeon.IsTileValid(nextX, nextY))
		{
			x = nextX;
			y = nextY;
		}
	}
};