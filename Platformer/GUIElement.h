#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GUIElements.h"
using namespace std;
using namespace sf;
class GUIElement
{
public:
	GUIElement(string Text, Vector2f Position, string Type);
	RectangleShape rect;
	void CreateElement();
	void MousePressed();
	void MouseReleased();
	void MouseHovered();
	void SoftRelease();
	bool IsPressed;
	void(*ButtonFunction)();
	~GUIElement();

	string Text, Type;
	Vector2f Location, Size;
	Color color;
	GUIElementButton* Button;
	GUIElementComboBox* ComboBox;
private:
	 
};

