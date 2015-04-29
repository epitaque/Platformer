#include "LevelGUI.h"


LevelGUI::LevelGUI(string LevelName)
{
	Level LevelTest(LevelName);
	LevelTest.Load();

	RenderWindow window(VideoMode(1280, 720), "Platformer:" + LevelName);
	View view(Vector2f(0, 0), Vector2f(1280, 720)); //These numbers can be scaled to zoom it out

	Player Player(Player(LevelTest.PlayerSpawn->rect.getPosition(), Vector2f(64, 64), Color::Blue, &LevelTest));
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) //If theres any event that is supposed to close the window, do that and deallocate everything.
		{
			if (event.type == Event::Closed)
			{
				cout << "Closing...\n";
				//LevelTest.Save();
				//cout << "Successfully saved level.\n";
				window.close();
				cout << "Successfully closed window.\n";
				goto stop;
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
		}

		Player.Move(&view); //HOLY SHIT SO MANY ADDRESSES
		window.clear(Color::White); //Make background white
		Player.Update();  //Update the coordinates of Player
		window.setView(view); //Has to be called every frame I read somewhere on the SFML tutorials
		LevelTest.Draw(&window); //"Draws" all of the blocks on the window
		window.draw(Player.rect); //Draw player
		view.setCenter(Vector2f(Player.rect.getPosition().x + ((Player.rect.getSize().x) / 2), Player.rect.getPosition().y + (Player.rect.getSize().y) / 2) ); //Centers camera on player


		window.display(); 
	}
	stop:
	cout << "Successfully exited this levelGUI.\n";
}


LevelGUI::~LevelGUI()
{
}
