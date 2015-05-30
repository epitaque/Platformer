#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "ElementButton.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
//#include "ElementComboBox.h"

using namespace sf;
using namespace std;

class GUI
{
public:
	GUI::GUI();
	GUI::GUI(string GUIFileName, RenderWindow* window, GUI* CurrentGUI);
	RenderWindow *window;
	GUI* CurrentGUI;
	~GUI();
	void Update();
private:

	void ParseElements();
	void Draw();

	bool MouseIsClicked;
	int MouseX, MouseY;
	int ButtonX, ButtonY;

	vector<ElementButton*> ButtonStack;
	//vector<ElementComboBox*> ComboBoxStack;
	
	string GUIFileName;

	vector<string> ParseText(string Value);
	Color ParseColor(string Value);
	Vector2f ParseLocation(string Value);
	Vector2f ParseSize(string Value);
	boost::function<void()> ParseFunction(string Value);
};

