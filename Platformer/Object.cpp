#include <SFML/Graphics.hpp>
#include "Object.h"

using namespace sf;


Object::Object(Vector2f position, Vector2f size, Color color) //Constructor converts paramaters to variables
{
	rect.setPosition(position);
	rect.setSize(size);
	rect.setFillColor(color);
}

void Object::Update()
{
	bottom = rect.getPosition().y + rect.getSize().y;
	top = rect.getPosition().y;
	right = rect.getPosition().x + rect.getSize().x;
	left = rect.getPosition().x;
}
bool Object::Collision(Object p)
{
	if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	return true;
}
