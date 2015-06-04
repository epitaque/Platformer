#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GUIForwardDeclarations.h"

class Element
{
public:
	Element();
	~Element();
	void SetCurrentGUI(GUI* CurrentGUI); 
	GUI* CurrentGUI;
	void ExecuteFunction(std::string Type, std::string Value);
	sf::RenderWindow* WindowA;
	void ReplaceGUI(std::string Value);
protected:

private:
	
};

