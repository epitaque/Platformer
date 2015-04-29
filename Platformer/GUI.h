#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GUI
{
public:
	GUI();
	~GUI();
	void CreateButton(Vector2f Position, string Text);
};

