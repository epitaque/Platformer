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

	void SetLocation(Vector2f Location);
	void SetLocation(Vector2f Location, Vector2u WindowDimensions);
	void SetPressColor(Color color);
	void SetInteriorColor(Color color);
	void SetOutlineColor(Color color);
	void SetTextColor(Color color);
	void SetPressTextColor(Color color);
	void SetText(string TextA);
	void SetSize(Vector2f Size);
	void SetFontSize(int FontSize);


	Vector2f GetLocation();

	bool IsReleased;
	bool IsPressed;

	bool GetReleasedStatus();
	void(*ButtonFunction)();
	Text text;
	
private: 
	Vector2f Size;
	Font font;
	Vector2f Location;
	Color InteriorColor;
	Color OutlineColor;
	Color PressColor; 
	Color PressTextColor;
	Color TextColor;
};


