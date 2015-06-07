#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "GUIForwardDeclarations.h"

using namespace sf;
using namespace std;

class GUI
{
public:
	GUI::GUI(string GUIFileName, sf::RenderWindow* window);
	GUI::GUI(string GUIFileName, sf::RenderWindow* window, GUI* CurrentGUI);
	sf::RenderWindow *window;
	GUI* CurrentGUI;
	~GUI();

	string GUIFileName;

	void SetCurrentGUI(GUI* CurrentGUI);
	void Update();
private:
	void ParseElements();
	void Draw();

	bool MouseIsClicked;
	int MouseX, MouseY;
	int ButtonX, ButtonY;

	vector<ElementButton*> ButtonStack;
	//vector<ElementComboBox*> ComboBoxStack;

	vector<string> GUI::ParseFunction(string Value);

	vector<string> ParseText(string Value);
	Color ParseColor(string Value);
	Vector2f ParseLocation(string Value);
	Vector2f ParseSize(string Value);
};

