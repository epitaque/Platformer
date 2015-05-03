#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class ElementComboBox
{
public:
	ElementComboBox(Vector2f Location, string Text, Vector2f Size, Color color);
	ElementComboBox();
	void Draw();
private:
	Vector2f Size;
	string StringText;
	Vector2f Location;
	Text text;
	Color color;
	Font font;
};


