#include "GUI.h"

using namespace sf;
using namespace std;

GUI::GUI(string GUIFileName, sf::RenderWindow* window)
{
	this->window = window;
	this->GUIFileName = GUIFileName;
	ParseElements();
	GUIFunctions = new GUIFunction;
}

GUI::~GUI()
{
	for (int i = 0; i < ButtonStack.size(); i++)
	{
		delete ButtonStack.at(i);
	}
}

void GUI::SetCurrentGUI(GUI* CurrentGUI) //Also creates a GUIFunction
{
	cout << "Setting CurrentGUI. CurrentGUI address = '" << CurrentGUI << endl;
	this->CurrentGUI = CurrentGUI;
	GUIFunctions->SetCurrentGUI(this->CurrentGUI);
	cout << "Setting GUIFunctions' CurrentGUI. GUIFunctions->CurrentGUI = '" << GUIFunctions->CurrentGUI << endl;
	cout << "GUIFunctions->CurrentGUI->window = " << GUIFunctions->CurrentGUI->window << endl;
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
					ButtonStack.push_back(new ElementButton(GUIFunctions));
					type = "Button";
				}
				/*else if (line == "ComboBox")
				{
					//ComboBoxStack.push_back(new ElementComboBox(window));
					ComboBoxStack.front()->AddButton(new ElementButton);
					type = "ComboBox";
				} */
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
				if (variable == "OnClickInteriorColor")
				{
					ButtonStack.back()->SetOnClickInteriorColor(ParseColor(value));
				}
				else if (variable == "OnClickTextColor")
				{
					ButtonStack.back()->SetOnClickTextColor(ParseColor(value));
				}
				else if (variable == "OnHoverInteriorColor")
				{
					ButtonStack.back()->SetOnHoverInteriorColor(ParseColor(value));
				}
				else if (variable == "OutlineColor")
				{
					ButtonStack.back()->SetOutlineColor(ParseColor(value));
				}
				else if (variable == "InteriorColor")
				{
					ButtonStack.back()->SetInteriorColor(ParseColor(value));
				}
				else if (variable == "Position") 
				{
					ButtonStack.back()->SetLocation(ParseLocation(value), window->getSize());
				}
				else if (variable == "Text") 
				{
					ButtonStack.back()->SetText(value);
				}
				else if (variable == "FontSize")
				{
					ButtonStack.back()->SetFontSize(atoi(value.c_str()));
				}
				else if (variable == "Size")
				{
					ButtonStack.back()->SetSize(ParseSize(value));
				}
				else if (variable == "Function")
				{
					vector<string> FunctionA = ParseFunction(value);
					cout << "Parsed function. Function = '" << FunctionA.at(0) << "', Value = '" << FunctionA.at(1) << "'.\n";
					ButtonStack.back()->SetFunction(FunctionA.at(0), FunctionA.at(1));
				}
			}
		
			/*else if (type == "ComboBox") 
			{
				if (variable == "OnClickInteriorColor")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetOnClickInteriorColor(ParseColor(value));
				}
				else if (variable == "OnHoverInteriorColor")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetOnHoverInteriorColor(ParseColor(value));
				}
				else if (variable == "TextOnClickColor")
				{
					ComboBoxStack.back()->ButtonStack.front()->SetOnClickTextColor(ParseColor(value));
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
			} */
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

vector<string> GUI::ParseFunction(string Value)
{
	string FunctionString;
	string ValueString;
	//cout << "Parsing a function." << endl;
	for (int i = 0; i < Value.length(); i++)
	{
		if (Value.at(i) == '(')
		{
			//cout << "Encountered '('. Starting ValueString parsing.\n";
			i++;
			for (i; i < Value.length() && Value.at(i) != ')'; i++)
			{
				ValueString += Value.at(i);
				//cout << "i = '" << i << "', ValueString = '" << ValueString << "'.\n";
			}
			break;
		}
		else
		{
			FunctionString += Value.at(i);
		}
		//cout << "i = '" << i << "', FunctionString = '" << FunctionString << "'.\n";
	}
	
	//cout << "Finished parsing function. FunctionString = '" << FunctionString << "', ValueString = '" << ValueString << "'\n";

	vector<string> foo = { FunctionString, ValueString };
	return foo;
}

void GUI::Update()
{
	MouseX = Mouse::getPosition(*window).x;
	MouseY = Mouse::getPosition(*window).y;

	Event EventA;

	while (window->pollEvent(EventA))
	{
		//cout << "Event type: " << EventA.type << endl;

		if (EventA.type == Event::MouseButtonPressed && EventA.mouseButton.button == Mouse::Left)
		{
			cout << "The left mouse button was pressed. \n";

			for (int i = 0; i < ButtonStack.size(); i++)
			{
				ButtonX = ButtonStack.at(i)->rect.getPosition().x;
				ButtonY = ButtonStack.at(i)->rect.getPosition().y;

				if (MouseX > ButtonX &&  // Is the click inside of the button?
					MouseX < ButtonX + ButtonStack.at(i)->rect.getSize().x &&
					MouseY > ButtonY &&
					MouseY < ButtonY + ButtonStack.at(i)->rect.getSize().y)
				{
					cout << "Click is inside of the button.\n";
					ButtonStack.at(i)->OnClick();
				}
			}
		}
		else if (EventA.type == Event::MouseButtonReleased && EventA.mouseButton.button == Mouse::Left)
		{
			cout << "The left mouse button was released. \n";
			for (int i = 0; i < ButtonStack.size(); i++)
			{
				ButtonX = ButtonStack.at(i)->rect.getPosition().x;
				ButtonY = ButtonStack.at(i)->rect.getPosition().y;
				if (ButtonStack.at(i)->IsClicked)
				{
					if (MouseX > ButtonX &&  // Is the release inside of the button?
						MouseX < ButtonX + ButtonStack.at(i)->rect.getSize().x &&
						MouseY > ButtonY &&
						MouseY < ButtonY + ButtonStack.at(i)->rect.getSize().y)
					{
						cout << "Release is inside of the button.\n";
						ButtonStack.at(i)->OnRelease();
					}
					else
					{
						ButtonStack.at(i)->OnSoftRelease();
					}
				}
			}
		}
		else if (EventA.type == Event::Closed)
		{
			window->close();
			break;
		}
	}
	// Check if it is hovering
	for (int i = 0; i < ButtonStack.size(); i++)
	{
		ButtonX = ButtonStack.at(i)->rect.getPosition().x;
		ButtonY = ButtonStack.at(i)->rect.getPosition().y;
		if (MouseX > ButtonX &&  // Is the release inside of the button?
			MouseX < ButtonX + ButtonStack.at(i)->rect.getSize().x &&
			MouseY > ButtonY &&
			MouseY < ButtonY + ButtonStack.at(i)->rect.getSize().y)
		{
			ButtonStack.at(i)->OnHover();
		}
		else if (ButtonStack.at(i)->IsHovered)
		{
			ButtonStack.at(i)->OnSoftRelease();
		}
	}
	
	for (int i = 0; i < ButtonStack.size(); i++)
	{
		ButtonStack.at(i)->Update(window);
	}
}