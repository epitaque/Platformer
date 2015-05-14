#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ElementButton.h"

using namespace sf;
using namespace std;

class ElementComboBox
{
public:
	ElementComboBox(RenderWindow* window);
	~ElementComboBox();

	void Update();
	void AddButton(ElementButton* ButtonA);
	void AddButton(string TextB);
	ElementButton* GetSelectedButton();

	vector<ElementButton*> ButtonStack;
	bool IsExpanded;
	Vector2f Location;
	float width, height; 
private:
	RenderWindow* window;
	void Draw();
	//ElementButton* SelectedButton;
	void Expand();
	void Contract();
};


