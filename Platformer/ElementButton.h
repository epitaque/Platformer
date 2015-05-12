#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class ElementButton
{
public:
	ElementButton();
	ElementButton(string Text, Vector2f Location, Vector2f Size, Color color, void(*ButtonFunction)());
	~ElementButton();

	RectangleShape rect;

	void Draw(RenderWindow* window);
	void PressButton();
	void SoftRelease();
	void ReleaseButton();
	void HoverButton();
	void HoverRelease();

	void SetLocation(Vector2f Location, Vector2u WindowDimensions);
	void SetColor(Color color);
	void SetText(string TextA);
	void SetSize(Vector2f Size);

	bool IsReleased;
	bool IsPressed;
	Color color;

	bool GetReleasedStatus();
	void(*ButtonFunction)();
	
private: 
	Vector2f Size;
	Font font;
	Vector2f Location;
	Text text;
};


