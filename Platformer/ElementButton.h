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

	// Main functions of the button
	void Update(RenderWindow* Window);
	void OnClick();
	void OnRelease();
	void OnSoftRelease();
	void OnHover();
	void SoftRelease();

	// Functions for changing attributes used in parsing
	void SetLocation(Vector2f Location);
	void SetLocation(Vector2f Location, Vector2u WindowDimensions);

	//Text and fill color
	void SetOnClickInteriorColor(Color color);
	void SetInteriorColor(Color color);
	void SetTextColor(Color color);
	void SetOnClickTextColor(Color color);
	void SetOnHoverInteriorColor(Color color);

	void SetOutlineColor(Color color);
	void SetText(string TextA);
	void SetSize(Vector2f Size);
	void SetFontSize(int FontSize);

	// Bools for the current status of the button
	bool IsHovered;
	bool IsSoftReleased;
	bool IsReleased;
	bool IsClicked;
	
private: 


	Vector2f GetLocation();	


	void Draw(RenderWindow* Window);
	void(*ButtonFunction)();
	void AnimateFadeInterior();
	void AnimateFadeText();

	Clock Clock;
	float AnimationDuration;
	float TimePercent;

	Vector2f Size;
	
	Font TextFont;
	Text Text;

	Vector2f Location;
	Color OutlineColor;

	Color TempColor;
	Color StartTextColor;
	Color EndTextColor;
	Color TextColor;
	Color OnClickTextColor;

	Color StartInteriorColor;
	Color EndInteriorColor;
	Color InteriorColor;
	Color OnClickInteriorColor, OnHoverInteriorColor;
};


