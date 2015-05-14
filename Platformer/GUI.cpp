#include "GUI.h"

using namespace sf;
using namespace std;

GUI::GUI(string GUIFileName, sf::RenderWindow* window)
{
	this->window = window;
	this->GUIFileName = GUIFileName;
	ParseElements();
}

void GUI::ParseElements()
{
	ifstream GUIFile;
	GUIFile.open(GUIFileName + ".txt", ios::in);

	string line, variable, value, type = "";

	cout << "Parsing GUI file in " << GUIFileName << ".txt\n";

	if (GUIFile.good()) // parse GUIFile
	{
		while (getline(GUIFile, line)) 
		{
			variable.erase();
			value.erase();
			if (line.empty() || (line.at(0) && line.at(1) == '/') )
			{
				continue;
			}
			else if (line.at(0) == '~') // parse ~<name>, after this is the element info	
			{ 
				line.erase(0, 1);
				if (line == "Button")  
				{
					ButtonStack.push_back(new ElementButton);
					type = "Button";
				}
				else if (line == "ComboBox")
				{
					ComboBoxStack.push_back(new ElementComboBox(window));
					ComboBoxStack.front()->AddButton(new ElementButton);
					type = "ComboBox";
				}
				else
				{
					cout << "ERROR: Unknown element. Types are ComboBox and Button ATM.";
				}
				cout << "Element type: " << type << endl;
				continue;
			}

			// parse <variable>=<value> for the line
			else 
			{
				for (int w = 0; line.at(w) != '=' && w < line.length(); w++) 
				{
					variable = variable + line.at(w);
				}
				for (int v = variable.length() + 1; v < line.length(); v++) 
				{
					value = value + line.at(v);
				}
				cout << "\nVariable: '" << variable << "' Value: '" << value << "'\n";
			}

			//figure out the type then parse the variables
			if (type == "Button")
			{
				if (variable == "PressColor")
				{
					ButtonStack.back()->SetPressColor(ParseColor(value));
				}
				else if (variable == "TextPressColor")
				{
					ButtonStack.back()->SetPressTextColor(ParseColor(value));
				}
				else if (variable == "OutlineColor")
				{
					ButtonStack.back()->SetOutlineColor(ParseColor(value));
				}
				else if (variable == "InteriorColor")
				{
					ButtonStack.back()->SetInteriorColor(ParseColor(value));
				}
				else if (variable == "location") 
				{
					ButtonStack.back()->SetLocation(ParseLocation(value), window->getSize());
				}
				else if (variable == "text") 
				{
					ButtonStack.back()->SetText(value);
				}
				else if (variable == "fontsize")
				{
					ButtonStack.back()->SetFontSize(atoi(value.c_str()));
				}
				else if (variable == "size")
				{
					ButtonStack.back()->SetSize(ParseSize(value));
				}
			}
		
			else if (type == "ComboBox") 
			{
				if (variable == "PressColor")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetPressColor(ParseColor(value));
				}
				else if (variable == "TextPressColor")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetPressTextColor(ParseColor(value));
				}
				else if (variable == "OutlineColor")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetOutlineColor(ParseColor(value));
				}
				else if (variable == "InteriorColor")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetInteriorColor(ParseColor(value));
				}
				else if (variable == "location")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetLocation(ParseLocation(value), window->getSize());
				}
				else if (variable == "text")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetText(value);
					vector<string> StrA = ParseText(value);
					ComboBoxStack.back()->ButtonStack.front()->SetText(StrA.at(0));
					for (int i = 1; i < StrA.size(); i++)
					{						
						ComboBoxStack.back()->AddButton(StrA.at(i));
					}
				}
				else if (variable == "fontsize")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetFontSize(atoi(value.c_str()));
				}
				else if (variable == "size")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetSize(ParseSize(value));
				}
				else if (variable == "text")
				{ //work on text separation
					ComboBoxStack.back()->AddButton(value);
				}
			} 
		}

	}
	else
	{
		cout << "ERROR: GUI file does not exist or is invalid!\n";
	}

	GUIFile.close();
}

vector<string> GUI::ParseText(string Value)
{
	Value = Value + ' ';
	
	vector<string> strarray;
	string curstr;
	cout << "Parsing text of gui...";
	for (int i = 0; i < Value.size(); i++)
	{
		if (Value.at(i) == ',' || Value.at(i) == ' ')
		{
			strarray.push_back(curstr);
			curstr = "";
		}
		else
		{
			curstr = curstr + Value.at(i);
		}
	}
	return strarray;
}

Color GUI::ParseColor(string Value)
{
	Value = Value + ' ';

	//for loop variables
	Color color;
	int coloriterator = 0;
	string rgba = "";


	cout << "Color of button #" << ButtonStack.size() << " is parsing.\n";
	for (int i = 0; i < Value.size(); i++)
	{
		if (Value.at(i) == ',' || Value.at(i) == ' ')
		{
			if (coloriterator == 0)
			{
				color.r = atoi(rgba.c_str());
				cout << "R = " << rgba << endl;
			}
			else if (coloriterator == 1)
			{
				color.g = atoi(rgba.c_str());
				cout << "G = " << rgba << endl;
			}
			else if (coloriterator == 2)
			{
				color.b = atoi(rgba.c_str());
				cout << "B = " << rgba << endl;
			}
			else if (coloriterator == 3)
			{
				color.a = atoi(rgba.c_str());
				cout << "A = " << rgba << endl;
				break;
			}
			else
			{
				cout << "WARNING: Too many arguments for the color variable in button " << ButtonStack.size() << "!\n";
			}
			coloriterator++;
			rgba = "";
		}
		else
		{
			rgba = rgba + Value.at(i);
			cout << "Added " << int(Value.at(i) - '0') << endl;
		}
	}
	return color;
}

Vector2f GUI::ParseLocation(string Value)
{
	Vector2f Location;
	string str;

	Value = Value + ' ';

	//for loop variable
	for (int i = 0; i < Value.length(); i++)
	{
		if (Value.at(i) == ',')
		{
			Location.x = atoi(str.c_str());
			str = "";
			cout << "Location of button #" << ButtonStack.size() << " is parsing. X = " << Location.x << "%";
		}
		else if (Value.at(i) == ' ')
		{
			Location.y = atoi(str.c_str());
			cout << ", Y = " << Location.y << "%" << endl;
			break;
		}
		else if (Value.at(i) == '%')
		{
			continue;
		}
		else
		{
			str = str + Value.at(i);
		}
	}
	return Location;
}
Vector2f GUI::ParseSize(string Value)
{
	cout << "Size of button #" << ButtonStack.size() << " is parsing. " << endl;
	Vector2f Size;
	string str = "";

	Value = Value + ' ';

	//for loop variable
	for (int i = 0; i < Value.length(); i++)
	{
		if (Value.at(i) == ',')
		{
			Size.x = atoi(str.c_str());
			str = "";
			cout << "X = " << Size.x << endl;
		}
		else if (Value.at(i) == ' ')
		{
			Size.y = atoi(str.c_str());
			cout << "Y = " << Size.y << endl;
			goto stop;
		}
		else
		{
			str = str + Value.at(i);
			cout << "Str = " << str << endl;
		}
	}
	stop:
	return Size;
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
	for (int i = 0; i < ButtonStack.size(); i++)
	{
		//cout << "Button number: " << i << endl;
		if (ButtonStack.at(i)->IsPressed) // Is the button being pressed?
		{								  // Yes
			cout << "Button " << i << " isPressed.\n";
			if (!Mouse::isButtonPressed(Mouse::Left)) // Is the mouse button not being pressed
			{										  // Yes
				if (Mouse::getPosition(*window).x > ButtonStack.at(i)->rect.getPosition().x && // Is the click inside of the button?
					Mouse::getPosition(*window).x < ButtonStack.at(i)->rect.getPosition().x + ButtonStack.at(i)->rect.getSize().x &&
					Mouse::getPosition(*window).y > ButtonStack.at(i)->rect.getPosition().y &&
					Mouse::getPosition(*window).y < ButtonStack.at(i)->rect.getPosition().y + ButtonStack.at(i)->rect.getSize().y)
				{																				// Yes
					cout << "Click is inside of the button.\n";
					ButtonStack.at(i)->ReleaseButton();	// Then release the button
					continue;
				}
				else
				{																				// No
					cout << "Click is not inside of the button. \n";
					cout << "Mouse.x of '" << Mouse::getPosition(*window).x << "' !> Button.rect.x of '" << ButtonStack.at(i)->rect.getPosition().x << "'\n";
					cout << "Mouse.x of '" << Mouse::getPosition(*window).x << "' !< Button.rect.x  + Button.rect.size.x of '" << ButtonStack.at(i)->rect.getPosition().x + ButtonStack.at(i)->rect.getSize().x << "'\n";
					cout << "Mouse.y of '" << Mouse::getPosition(*window).y << "' !< Button.rect.y of '" << ButtonStack.at(i)->rect.getPosition().y << "'\n";
					cout << "Mouse.y of '" << Mouse::getPosition(*window).y << "' !> Button.rect.y  + Button.rect.size.y of '" << ButtonStack.at(i)->rect.getPosition().y + ButtonStack.at(i)->rect.getSize().y << "'\n";


					ButtonStack.at(i)->SoftRelease(); // Soft release the button
					continue;
				}
			}
			else
			{								// No
				continue; // Do nothing
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Left) && // Is the mouse button being pressed? Yes
			Mouse::getPosition(*window).x > ButtonStack.at(i)->rect.getPosition().x && // Is the click is inside the button?
			Mouse::getPosition(*window).x < ButtonStack.at(i)->rect.getPosition().x + ButtonStack.at(i)->rect.getSize().x &&
			Mouse::getPosition(*window).y > ButtonStack.at(i)->rect.getPosition().y &&
			Mouse::getPosition(*window).y < ButtonStack.at(i)->rect.getPosition().y + ButtonStack.at(i)->rect.getSize().y)
		{																			// Yes
			ButtonStack.at(i)->PressButton(); // Press the button
			cout << "button has been pressed\n";
		}
		else if (Mouse::isButtonPressed(Mouse::Left))
		{
		/*	cout << "Click is not inside of the button. \n";
			cout << "Mouse.x of '" << Mouse::getPosition(*window).x << "' !> Button.rect.x of '" << ButtonStack.at(i)->rect.getPosition().x << "'\n";
			cout << "Mouse.x of '" << Mouse::getPosition(*window).x << "' !< Button.rect.x  + Button.rect.size.x of '" << ButtonStack.at(i)->rect.getPosition().x + ButtonStack.at(i)->rect.getSize().x << "'\n";
			cout << "Mouse.y of '" << Mouse::getPosition(*window).y << "' !< Button.rect.y of '" << ButtonStack.at(i)->rect.getPosition().y << "'\n";
			cout << "Mouse.y of '" << Mouse::getPosition(*window).y << "' !> Button.rect.y  + Button.rect.size.y of '" << ButtonStack.at(i)->rect.getPosition().y + ButtonStack.at(i)->rect.getSize().y << "'\n";
	*/	}
	}

	/*if (Mouse::isButtonPressed(Mouse::Left)) //Output information code
	{
	cout << "the right button was pressed" << endl;
	cout << "mouse x: " << Mouse::getPosition(*window).x << endl;
	cout << "mouse y: " << Mouse::getPosition(*window).y << endl;
	} */

	for (int i = 0; i < ComboBoxStack.size(); i++)
	{
		ComboBoxStack.at(i)->Update();
	}

	Draw();
}

void GUI::Draw()
{
	for (int i = 0; i < ButtonStack.size(); i++)
	{
		ButtonStack.at(i)->Draw(window);
	}
	/*for (int i = 0; i < ComboBoxStack.size(); i++)
	{
		ComboBoxStack.at(i)->Draw();
	}*/
}

