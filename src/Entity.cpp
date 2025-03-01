#include "Entity.h"
#include "Dungeon.h"

Entity::Entity(Dungeon& dungeon, EntityType type) : dungeon(dungeon), type(type) { }

void Entity::Draw()
{
	if (type == Player)
		DrawTextureV(texture, Vector2Multiply(position, { TILE_SIZE, TILE_SIZE }), WHITE);
}

void Entity::Move(Vector2 direction)
{
	Vector2 newPosition = Vector2Add(position, direction);

	if (newPosition.x < 1 || newPosition.x >= DUNGEON_WIDTH - 1 || newPosition.y < 1 || newPosition.y >= DUNGEON_HEIGHT - 1) return;
	if (dungeon.GetTile(newPosition) != FLOOR) return;

	position = newPosition;
}

void Entity::Walk()
{
	static Vector2 prevDirection;
	static const Vector2 directions[] =
	{
		{  0,  1 },
		{  0, -1 },
		{  1,  0 },
		{ -1,  0 }
	};

	dungeon.SetTile(position, FLOOR);

	while (healthPoints > 0)
	{
		//Random Direction
		Vector2 choosenDirection;
		do {
			int randomDirection = GetRandomValue(0, 3);
			choosenDirection = directions[randomDirection];
		} while ((choosenDirection.x == -prevDirection.x && choosenDirection.y == -prevDirection.y));
		prevDirection = choosenDirection;

		//Move
		Vector2 newPosition = Vector2Add(position, choosenDirection);
		if (newPosition.x < 1 || newPosition.x >= DUNGEON_WIDTH - 1 || newPosition.y < 1 || newPosition.y >= DUNGEON_HEIGHT - 1) continue;

		int oldIndex = dungeon.IndexFromPosition(position);
		int newIndex = dungeon.IndexFromPosition(newPosition);

		dungeon.SetTile(position, FLOOR);
		position = newPosition;

		healthPoints -= 1;
	}
}
