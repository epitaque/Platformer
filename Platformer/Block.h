#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Side.h"

using namespace sf;

class Block : public Object
{
public:
	Block();
	Block(Vector2f position);
	string name;
	Side Top;
	Side Bot;
	Side Left;
	Side Right;
	Texture* TextureA;
	char letter;
	void OutInfo();
	bool PlayerSpawn;
};

