#pragma once
#include <iostream>
#include "GUI.h"
#include <SFML/Window.hpp>

using namespace std;

class GUITempReplacer
{
public:
	GUITempReplacer(string Value, sf::RenderWindow* Window, GUI* CurrentGUI);
	~GUITempReplacer();
};

