#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include "GUIFunctions.h"
#include "ElementButton.h"
//#include "ElementComboBox.h"

//
// Forward declarations because of cirular dependency. GUIElements' 
// OnClick functions need a GUI to actually perform the function,
// and GUIs need the GUIElements to create the elements. 
//---------------------------------------------------------------

class GUIFunction;
class ElementButton;

using namespace sf;
using namespace std;

class GUI
{
public:
	GUI::GUI(string GUIFileName, RenderWindow* window);
	RenderWindow *window;
	GUI* CurrentGUI;
	~GUI();

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
	
	GUIFunction* GUIFunctions;
	string GUIFileName;

	vector<string> GUI::ParseFunction(string Value);

	vector<string> ParseText(string Value);
	Color ParseColor(string Value);
	Vector2f ParseLocation(string Value);
	Vector2f ParseSize(string Value);
};

