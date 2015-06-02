/*#include "EventManager.h"

 
EventManager::EventManager(RenderWindow* window, string BindingFileName)
{
	this->window = window;
	ParseBindings(BindingFileName)
}


EventManager::~EventManager()
{
}

void EventManager::ParseBindings(string BindingFileName)
{
	ifstream BindingFile;
	BindingFile.open(BindingFileName, ios::in);

	string line, variable, value = "";

	cout << "Parsing Bindings file in " << BindingFileName << ".txt\n";

	if (BindingFile.good()) // parse BindingFile
	{
		while (getline(BindingFile, line))
		{
			variable.erase();
			value.erase();
			if (line.empty() || (line.at(0) && line.at(1) == '/'))
			{
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
			if (variable == "MoveUp")
			{
				
			}

			else if (variable == "MoveDown")
			{
				if ()
			}
		}

	}
	else
	{
		cout << "ERROR: GUI file does not exist or is invalid!\n";
	}

	BindingFile.close();
}

void EventManager(string key)
{
	if (key == "ArrowUp")

}
*/
