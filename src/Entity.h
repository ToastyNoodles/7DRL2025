#pragma once
#include "raylib.h"
#include "raymath.h"

class Dungeon;

enum EntityType
{
	Walker = 0,
	Player = 1,
	Enemy = 2
};

class Entity
{
public:
	Entity(Dungeon& dungeon, EntityType type);
	Dungeon& dungeon;
	EntityType type;
	Vector2 position;
	int healthPoints;
	int actionPoints;
	Texture texture;

	void Draw();
	void Move(Vector2 direction);
	void Walk();
};