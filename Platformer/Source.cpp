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
	GUI* CurrentGUI = new GUI("menugui.txt", &window);
	CurrentGUI->SetCurrentGUI(CurrentGUI); //this line is so weird
	GUI* TestGUI = CurrentGUI;
	Clock clock;
	while (window.isOpen())
	{
		if (CurrentGUI != TestGUI)
		{
			cout << "New GUI in the main loop.\n";
			TestGUI = CurrentGUI;
		}
		if (clock.getElapsedTime().asSeconds() > 2)
		{
			cout << "CurrentGUI Address = " << CurrentGUI << endl;
			cout << "CurrentGUI name = " << CurrentGUI->GUIFileName << endl;

			clock.restart();
		}
		window.clear(Color::White);
		Event event;
		/*while (window.pollEvent(event)) //If theres any event that is supposed to close the window, do that and deallocate everything.
		{ 
			if (event.type == Event::Closed)
			{
				cout << "Closing...\n";
				window.close();
				cout << "Successfully closed window.\n";
				return 0;
			}
			else if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta > 0)
				{
					view.zoom(0.7f);
					cout << "Zooming in... \n";
				}
				else if (event.mouseWheel.delta < 0)
				{
					view.zoom(1.3f);
					cout << "Zooming out... \n";
				}
			}
		} */
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		window.setView(view);
		CurrentGUI->Update();
		view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
		window.display();
	}

	return 0;
} 
