/*#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;

class EventManager
{
public: 
	EventManager(RenderWindow* window, string BindingFileName);
	~EventManager();
	void Update();
private:
	Event event;
	RenderWindow* window;
	void ParseBindings(string BindingFileName);
	void GetKey(string key);
};

*/
