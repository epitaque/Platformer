#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GUI.h"

using namespace std;

class GUI;

class GUIFunction
{
public:
	GUIFunction();
	void ExecuteFunction(string Type, string Value);
	void ReplaceGUI(string Value);
	void SetCurrentGUI(GUI* CurrentGUI); 
	GUI* CurrentGUI;
	~GUIFunction();
private:
	RenderWindow* window;
};

