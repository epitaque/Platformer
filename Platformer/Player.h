#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Level.h"

using namespace sf;

class Player : public Object
{
public:
	Player(Level *LevelZ);
	Player(Vector2f position, Vector2f size, Color color, Level *LevelZ);
	
	Block* PastBlock;
	Block* CB; // Collision Block
	Level* LevelA;
	int TempIterator;
	Vector2f Velocity;

	float Gravity;
	float Speed, Acceleration, Jump;
	void Move(View* View);
	bool HandleCollision();
private:
	bool onSurface;
};



