#pragma once
#include "Dungeon.h"

struct EntityTextures
{
	Texture playerTexture;
	Texture slimeTexture;
	Texture itemTexture;

	void LoadTextures()
	{
		playerTexture = LoadTexture("res/player.png");
		slimeTexture = LoadTexture("res/snake.png");
		itemTexture = LoadTexture("res/item.png");
	}
} static entityTextures;

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
	Player(int spawnX, int spawnY)
	{
		x = spawnX;
		y = spawnY;
		isActive = true;
		texture = entityTextures.playerTexture;
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
			dungeon.SetTile(x, y, FLOOR);
			x = nextX;
			y = nextY;
			dungeon.SetTile(x, y, PLAYER);
			dungeon.SetPlayerTurn(false);
		}
	}
};

struct Enemy : public Entity
{
	Enemy(int spawnX, int spawnY)
	{
		x = spawnX;
		y = spawnY;
		isActive = true;
		texture = entityTextures.slimeTexture;
	}

	void Draw() override
	{
		int worldX = x * TILE_SIZE;
		int worldY = y * TILE_SIZE;
		DrawTexture(texture, worldX, worldY, MAROON);
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
			dungeon.SetTile(x, y, FLOOR);
			x = nextX;
			y = nextY;
			dungeon.SetTile(x, y, ENEMY);
		}
	}
};

struct Item : public Entity
{
	Item(int spawnX, int spawnY)
	{
		x = spawnX;
		y = spawnY;
		isActive = true;
		texture = entityTextures.itemTexture;
	}

	void Draw() override
	{
		int worldX = x * TILE_SIZE;
		int worldY = y * TILE_SIZE;
		DrawTexture(texture, worldX, worldY, YELLOW);
	}

	void Update(Dungeon& dungeon) override
	{
		
	}
};