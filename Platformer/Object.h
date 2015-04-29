#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Object
{
public:
	RectangleShape rect;
	Object() {};
	Object(Vector2f position, Vector2f size, Color color);
	void Update();
	bool Collision(Object p);
	float bottom, top, left, right;
};

