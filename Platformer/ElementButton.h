#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class ElementButton
{
public:
	ElementButton(string Text, Vector2f Location, Vector2f Size, Color color, void(*ButtonFunction)());
	void Draw(RenderWindow* window);
	void PressButton();
	void SoftRelease();
	void ReleaseButton();
	void HoverButton();
	void HoverRelease();
	RectangleShape rect;
	bool IsPressed;
	~ElementButton();
private:
	Vector2f Location;
	Vector2f Size;
	Text text;
	Font font;
	Color color;
	void(*ButtonFunction)();
};


