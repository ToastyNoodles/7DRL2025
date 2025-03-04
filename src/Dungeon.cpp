#include "Dungeon.h"
#include "Entity.h"

Dungeon::Dungeon(int width, int height) : width(width), height(height), tiles(width * height, NONE), isPlayerTurn(true), currentFloor(1)
{
	wallTexture = LoadTexture("res/wall.png");
	exitTexture = LoadTexture("res/exit.png");
	entityTextures.LoadTextures();

	Generate();
}

void Dungeon::Generate()
{
	std::fill(tiles.begin(), tiles.end(), NONE);
	entities.clear();

	int x = width / 2;
	int y = height / 2;
	tiles[y * width + x] = FLOOR;

	int lastDirection = -1;

	//Modified drunk walk
	for (int i = 0; i < (500 + (currentFloor * 100)); i++)
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

	//Surround floors with walls
	int directions[8][2] = {
		{ 0, -1}, // Up
		{ 0,  1}, // Down
		{-1,  0}, // Left
		{ 1,  0}, // Right
		{-1, -1}, // Top-left
		{ 1, -1}, // Top-right
		{-1,  1}, // Bottom-left
		{ 1,  1}  // Bottom-right
	};

	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i] == FLOOR)
		{
			int x = i % width;
			int y = i / width;

			for (const auto& dir : directions)
			{
				int newX = x + dir[1];
				int newY = y + dir[0];

				if (newX >= 0 && newX < width && newY >= 0 && newY < height)
				{
					if (tiles[newY * width + newX] != FLOOR)
					{
						tiles[newY * width + newX] = WALL;
					}
				}
			}
		}
	}

	SpawnExit();
	SpawnPlayer();
	SpawnEnemies();
	SpawnItems();
}

void Dungeon::Update()
{
	if (isPlayerTurn)
	{
		player->Update(*this);

		int playerTileIndex = player->y * width + player->x;
		if (tiles[playerTileIndex] == EXIT)
		{
			Generate();
			currentFloor += 1;
		}
	}

	if (!isPlayerTurn)
	{
		for (Entity* entity : entities)
		{
			if (entity->isActive)
				entity->Update(*this);
		}
		isPlayerTurn = true;
	}
}

void Dungeon::Draw()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		int tileX = i % width;
		int tileY = i / width;
		int worldX = tileX * TILE_SIZE;
		int worldY = tileY * TILE_SIZE;

		if (tiles[i] == WALL)
		{
			DrawTexture(wallTexture, worldX, worldY, LIGHTGRAY);
		}
		else if (tiles[i] == EXIT)
		{
			DrawTexture(exitTexture, worldX, worldY, LIGHTGRAY);
		}
	}

	for (Entity* entity : entities)
	{
		if (entity->isActive)
			entity->Draw();
	}

	player->Draw();

	//DEBUG TILE STATES
	//for (int i = 0; i < tiles.size(); i++)
	//{
	//	int tileX = i % width;
	//	int tileY = i / width;
	//	int worldX = tileX * TILE_SIZE;
	//	int worldY = tileY * TILE_SIZE;
	//
	//	if (tiles[i] == FLOOR)
	//	{
	//		DrawRectangle(worldX, worldY, 2, 2, YELLOW);
	//	}
	//	else if (tiles[i] == WALL)
	//	{
	//		DrawRectangle(worldX, worldY, 2, 2, DARKGREEN);
	//	}
	//	else if (tiles[i] == EXIT)
	//	{
	//		DrawRectangle(worldX, worldY, 2, 2, PURPLE);
	//	}
	//	else if (tiles[i] == PLAYER)
	//	{
	//		DrawRectangle(worldX, worldY, 2, 2, BLUE);
	//	}
	//	else if (tiles[i] == ENEMY)
	//	{
	//		DrawRectangle(worldX, worldY, 2, 2, RED);
	//	}
	//	else if (tiles[i] == NONE)
	//	{
	//		DrawRectangle(worldX, worldY, 2, 2, ORANGE);
	//	}
	//}
}

Vector2 Dungeon::GetPlayerPosition()
{
	return { (float)player->x, (float)player->y };
}

bool Dungeon::IsTileValid(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return false;
	}

	int index = y * width + x;
	if (tiles[index] == WALL || tiles[index] == ENEMY || tiles[index] == PLAYER)
	{
		return false;
	}

	return true;
}

void Dungeon::SetPlayerTurn(bool state)
{
	isPlayerTurn = state;
}

void Dungeon::SetTile(int x, int y, Tile type)
{
	if (tiles[y * width + x] != EXIT)
		tiles[y * width + x] = type;
}

Tile Dungeon::GetTile(int x, int y)
{
	return tiles[y * width + x];
}

std::vector<int> Dungeon::GetFloorIndices()
{
	std::vector<int> floorIndices;
	for (int i = 0; i < tiles.size(); i++)
	{
		int x = i % width;
		int y = i / width;
		if (tiles[i] == FLOOR && x != (width / 2) && y != (height / 2))
			floorIndices.push_back(i);
	}

	return floorIndices;
}

std::vector<int> Dungeon::GetFloorIndicesExcludingPlayerRadius(int radius)
{
	std::vector<int> floorIndices;
	int playerX = width / 2;
	int playerY = height / 2;

	for (int i = 0; i < tiles.size(); i++) 
	{
		if (tiles[i] == FLOOR) 
		{
			int x = i % width;
			int y = i / width;
			if (abs(x - playerX) > radius || abs(y - playerY) > radius) 
			{
				floorIndices.push_back(i);
			}
		}
	}

	return floorIndices;
}

void Dungeon::SpawnExit()
{
	std::vector<int> floorIndices = GetFloorIndicesExcludingPlayerRadius(20);
	if (floorIndices.empty())
	{
		TraceLog(LOG_ERROR, "No valid positions with constraint to spawn exit! Trying again! (1/2)");
		floorIndices = GetFloorIndicesExcludingPlayerRadius(10);
		if (floorIndices.empty())
		{
			TraceLog(LOG_ERROR, "No valid positions to spawn exit! Regenerating dungeon! (2/2)");
			Generate();
			return;
		}
	}

	int randomIndex = GetRandomValue(0, floorIndices.size() - 1);
	int exitIndex = floorIndices[randomIndex];
	tiles[exitIndex] = EXIT;
}

void Dungeon::SpawnPlayer()
{
	player = new Player(width / 2, height / 2);

	int x = width / 2;
	int y = height / 2;
	tiles[y * width + x] = PLAYER;
}

void Dungeon::SpawnEnemies()
{
	std::vector<int> floorIndices = GetFloorIndicesExcludingPlayerRadius(5);
	if (floorIndices.empty())
	{
		TraceLog(LOG_ERROR, "No valid positions with constraint to spawn enemy!");
		return;
	}

	int spawnLow = (currentFloor / 2);
	int spawnHigh = (int)pow(currentFloor, 1.1) - 1;
	TraceLog(LOG_INFO, "ENEMY SPAWNING |Floor: %i | Low: %i | High: %i", currentFloor, spawnLow, spawnHigh);
	int spawnCount = GetRandomValue(spawnLow, spawnHigh);
	for (int i = 0; i < spawnCount; i++)
	{
		int randomIndex = GetRandomValue(0, floorIndices.size() - 1);
		int tileIndex = floorIndices[randomIndex];
		int x = tileIndex % width;
		int y = tileIndex / width;

		Enemy* enemy = new Enemy(x, y);
		entities.push_back(enemy);

		tiles[y * width + x] = ENEMY;
	}
}

void Dungeon::SpawnItems()
{
	std::vector<int> floorIndices = GetFloorIndices();
	if (floorIndices.empty())
	{
		TraceLog(LOG_ERROR, "No valid positions to spawn items!");
		return;
	}

	int spawnLow = (currentFloor / 2);
	int spawnHigh = (currentFloor / 2);
	if (currentFloor < 2) { spawnLow = 1; spawnHigh = 1; }
	TraceLog(LOG_INFO, "ITEM SPAWNING | Floor: %i | Low: %i | High: %i", currentFloor, spawnLow, spawnHigh);
	int spawnCount = GetRandomValue(spawnLow, spawnHigh);
	for (int i = 0; i < spawnCount; i++)
	{
		int randomIndex = GetRandomValue(0, floorIndices.size() - 1);
		int tileIndex = floorIndices[randomIndex];
		int x = tileIndex % width;
		int y = tileIndex / width;

		Item* item = new Item(x, y);
		entities.push_back(item);

		tiles[y * width + x] = ITEM;
	}
}
