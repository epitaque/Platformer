#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "ElementButton.h"
#include "ElementComboBox.h"

using namespace sf;
using namespace std;

class GUI
{
public:
	GUI::GUI();
	GUI::GUI(string GUIFileName, RenderWindow* window);
	GUI* CurrentGUI;
	~GUI();
	void Update();
private:
	RenderWindow *window;
	void ParseElements();
	void Draw();
	vector<ElementButton*> ButtonStack;
	vector<ElementComboBox*> ComboBoxStack;
	
	string GUIFileName;

	Color ParseColor(string Value);
	Vector2f ParseLocation(string Value);
	Vector2f ParseSize(string Value);
};

