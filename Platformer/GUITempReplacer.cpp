#include "GUITempReplacer.h"
#include "GUI.h"
#include <SFML/Window.hpp>

GUITempReplacer::GUITempReplacer(string Value, sf::RenderWindow* Window, GUI* CurrentGUI)
{
	cout << "\n------------------------\n";
	cout << "        NEW GUI\n";
	cout << "------------------------\n\n";

	CurrentGUI->~GUI();
	cout << "ReplaceGUI Value = " << Value << endl;
	cout << "ReplaceGUI Window = " << Window << endl;
	CurrentGUI = NULL;

	cout << "ReplaceGUI CurrentGUI = " << CurrentGUI << endl;
	CurrentGUI = new GUI(Value, Window, CurrentGUI);
	cout << "New ReplaceGUI CurrentGUI = " << CurrentGUI << endl;

}


GUITempReplacer::~GUITempReplacer()
{
}
