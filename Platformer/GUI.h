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
	~GUI();
	void Update();
	void ParseElements(string GUIFileName);
private:
	RenderWindow *window;
	void Draw();
	vector<ElementButton*> ButtonStack;
	vector<ElementComboBox*> ComboBoxStack;
	Event event;
};

