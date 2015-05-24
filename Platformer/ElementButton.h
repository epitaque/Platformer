#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>

using namespace sf;
using namespace std;

class ElementButton
{
public:
	ElementButton();
	~ElementButton();

	RectangleShape rect;

	void Update();
	void OnClick();
	void OnRelease();
	void OnSoftRelease();
	void OnHover();

	// Functions used in parsing
	void SetLocation(Vector2f Location);
	void SetLocation(Vector2f Location, Vector2u WindowDimensions);
	void SetOnClickColor(Color color);
	void SetInteriorColor(Color color);
	void SetOutlineColor(Color color);
	void SetTextColor(Color color);
	void SetOnClickTextColor(Color color);
	void SetText(string TextA);
	void SetSize(Vector2f Size);
	void SetFontSize(int FontSize);

	bool IsHovered;
	bool IsReleased;
	bool IsClicked;
	
private: 

	void SoftRelease();



	Vector2f GetLocation();
	
	


	void Draw(RenderWindow* window);

	bool GetReleasedStatus();
	void(*ButtonFunction)();

	
	Clock Clock;
	int AnimationDuration;

	Vector2f Size;
	
	Font TextFont;
	Text Text;

	Vector2f Location;
	Color OutlineColor;

	Color StartTextColor;
	Color EndTextColor;
	Color TextColor;
	Color OnClickTextColor;

	Color StartInteriorColor;
	Color EndInteriorColor;
	Color InteriorColor;
	Color OnClickInteriorColor, OnHoverInteriorColor;
};


