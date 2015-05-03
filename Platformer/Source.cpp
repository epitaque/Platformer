#include <SFML/Graphics.hpp>
#include <iostream>
#include "LevelGUI.h"
#include "GUI.h"


using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(1280, 720), "Platformer");
	View view(Vector2f(0, 0), Vector2f(1280, 720)); //These numbers can be scaled to zoom it out
	window.setFramerateLimit(60);
	GUI *CurrentGUI;
	GUI MenuGUI("menugui.txt", &window, CurrentGUI);
	CurrentGUI = &MenuGUI;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) //If theres any event that is supposed to close the window, do that and deallocate everything.
		{
			if (event.type == Event::Closed)
			{
				cout << "Closing...\n";
				window.close();
				cout << "Successfully closed window.\n";
				return 0;
			}
		}

		CurrentGUI->Update();
		window.display();
	}

	LevelGUI TestLevel("level");
	return 0;
} 
