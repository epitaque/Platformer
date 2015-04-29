#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

template<class T>


class GUIElement
{
public:
	GUIElement(string Text, Vector2f Location, Vector2f Size, GUIElement* EventElement);
	~GUIElement();
	string Type;
	Vector2f Location;

};

class GUIElementButton
{
public:
	GUIElementButton(string Text, Vector2f Location, Vector2f Size, GUIElement* EventElement);
	~GUIElementButton();
};


