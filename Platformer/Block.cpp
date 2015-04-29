#include "Block.h"

using namespace sf;

Block::Block()
{
	rect.setSize(Vector2f(64, 64));
	if (TextureA != NULL)
		rect.setTexture(TextureA);
	PlayerSpawn = false;
}

Block::Block(Vector2f position) 
{
	rect.setPosition(position);
	rect.setSize(Vector2f(64, 64));
	if (TextureA != NULL)
		rect.setTexture(TextureA);
	PlayerSpawn = false;
}

void Block::OutInfo()
{
	// Sides
	std::cout << "PhasableTop: " << Top.Phasable << "\nPhasableBot: " << Bot.Phasable << "\nPhasableLeft: " << Left.Phasable << "\nPhasableRight: " << Right.Phasable << endl;
	// Texture
	std::cout << "TextureLocation: " << TextureA << endl;
	// Position
	std::cout << "Position: " << rect.getPosition().x << ", " << rect.getPosition().y << endl;
}