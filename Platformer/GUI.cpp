#include "GUI.h"

using namespace sf;
using namespace std;

GUI::GUI(string GUIFileName, sf::RenderWindow* window)
{
	this->window = window;
}

void GUI::ParseElements(string GUIFileName)
{
	ifstream GUIFile;
	string line, variable, value, side = "";
	GUIFile.open(GUIFileName + ".txt", ios::in);
	std::cout << "Parsing GUI file in " << GUIFileName << ".txt\n";
	// parse GUIFile
	if (GUIFile.good()) {
		while (getline(GUIFile, line)) 
		{
			variable.erase();
			value.erase();
			side.erase();
			if (line.empty())
				continue;
			if (line.at(0) == '~') { // parse ~<name>, after this is the block info	
				line.erase(0, 1);
				if (line == "Button")  
				BlockTemplates.push_back(new Block);
				BlockTemplates.back()->name = line;
				cout << "Starting creation of a block...\n";
				continue;
			}

			// parse <variable>=<value> for the line
			else {
				for (int w = 0; line.at(w) != '=' && w < line.length(); w++) {
					variable = variable + line.at(w);
				}
				for (int v = variable.length() + 1; v < line.length(); v++) {
					value = value + line.at(v);
				}
				cout << "Variable: '" << variable << "' Value: '" << value << "'\n";
			}

			// Letter
			if (variable == "letter") {
				BlockTemplates.back()->letter = value.at(0);
			}

			//PhasableSides 
			else if (variable == "PhasableSides")
			{
				if (value == "none") {
					BlockTemplates.back()->Top.Phasable = false;
					BlockTemplates.back()->Bot.Phasable = false;
					BlockTemplates.back()->Left.Phasable = false;
					BlockTemplates.back()->Right.Phasable = false;
				}
				else {
					value = value + ' ';
					for (int x = 0; x < value.length(); x++) {
						if (value.at(x) == ',' || x + 1 >= value.length()) {
							if (side == "left")
								BlockTemplates.back()->Left.Phasable = true;
							else if (side == "right")
								BlockTemplates.back()->Right.Phasable = true;
							else if (side == "top")
								BlockTemplates.back()->Top.Phasable = true;
							else if (side == "bot")
								BlockTemplates.back()->Bot.Phasable = true;
							else
								std::cout << "WARNING: Invalid side in PhasableSides in blocks.txt\n";
							cout << "Side " << side << " is phasable.\n";
							side = "";
						}
						else
							side = side + value.at(x);
					}
				}
			}

			// Texture
			else if (variable == "texture") {
				BlockTemplates.back()->TextureA = new Texture();
				BlockTemplates.back()->TextureA->loadFromFile("Levels/" + LevelFileName + "/Blocks/" + value);
			}

			// Spawn Point
			else if (variable == "spawn") {
				if (value == "true")
				{
					BlockTemplates.back()->PlayerSpawn = true;
				}
			}
		}

	}
	else
		std::cout << "ERROR: Block file does not exist or is invalid!\n";

	BlockFile.close();
}

GUI::~GUI()
{
	for (int i = 0; i < ButtonStack.size(); i++)
	{
		delete ButtonStack.at(i);
	}
	for (int i = 0; i < ComboBoxStack.size(); i++)
	{
		delete ComboBoxStack.at(i);
	}
}

void GUI::Update()
{
	while (window->pollEvent(event)) //Handle GUI input. 
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "the right button was pressed" << std::endl;
				std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				for (int i = 0; i < ButtonStack.size(); i++)
				{
					if (event.mouseButton.x < ButtonStack.at(i)->rect.getPosition().x || // If the click is inside the button...
						event.mouseButton.x > ButtonStack.at(i)->rect.getPosition().x + ButtonStack.at(i)->rect.getSize().x ||
						event.mouseButton.y < ButtonStack.at(i)->rect.getPosition().y ||
						event.mouseButton.y > ButtonStack.at(i)->rect.getPosition().y + ButtonStack.at(i)->rect.getSize().y)
						ButtonStack.at(i)->PressButton();
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "the right button was released" << std::endl;
				std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				for (int i = 0; i < ButtonStack.size(); i++)
				{
					if (event.mouseButton.x < ButtonStack.at(i)->rect.getPosition().x || // If the click release is inside the button and the button is currently pressed...
						event.mouseButton.x > ButtonStack.at(i)->rect.getPosition().x + ButtonStack.at(i)->rect.getSize().x ||
						event.mouseButton.y < ButtonStack.at(i)->rect.getPosition().y ||
						event.mouseButton.y > ButtonStack.at(i)->rect.getPosition().y + ButtonStack.at(i)->rect.getSize().y &&
						ButtonStack.at(i)->IsPressed)
					{
						ButtonStack.at(i)->ReleaseButton();
					}
					else if(ButtonStack.at(i)->IsPressed)
					{
						ButtonStack.at(i)->SoftRelease();
					}
				}
			}
		}
	}
}

void GUI::Draw()
{
	for (int i = 0; i < ButtonStack.size(); i++)
	{
		ButtonStack.at(i)->Draw();
	}
	for (int i = 0; i < ComboBoxStack.size(); i++)
	{
		ComboBoxStack.at(i)->Draw();
	}
}

GUI::~GUI()
{
}
