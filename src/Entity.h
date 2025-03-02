#pragma once
#include "Dungeon.h"

struct Entity
{
	int x, y;
	bool isActive;
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
	}

	void Draw() override
	{
		DrawRectangle(x * 16, y * 16, 16, 16, WHITE);
	}

	void Update(Dungeon& dungeon) override
	{
		int nextX = x, nextY = y;

		if (IsKeyPressed(KEY_W)) { nextY -= 1; }
		else if (IsKeyPressed(KEY_S)) { nextY += 1; }
		else if (IsKeyPressed(KEY_A)) { nextX -= 1; }
		else if (IsKeyPressed(KEY_D)) { nextX += 1; }

		if (dungeon.IsTileValid(nextX, nextY))
		{
			x = nextX;
			y = nextY;
		}
	}
};