#include "GUIFunctions.h"


GUIFunction::GUIFunction()
{
	
}

void GUIFunction::SetCurrentGUI(GUI* CurrentGUI)
{
	//cout << CurrentGUI;
	
	this->CurrentGUI = CurrentGUI;
	window = CurrentGUI->window;

}

void GUIFunction::ExecuteFunction(string Type, string Value)
{
	if (Type == "ReplaceGUI")
	{
		cout << "Switching GUIs...\n";
		ReplaceGUI(Value);
	}
	else
	{
		cout << "Unknown function\n";
	}
}

void GUIFunction::ReplaceGUI(string Value)
{
	//cout << CurrentGUI->window << endl;
	CurrentGUI->~GUI();
	CurrentGUI = new GUI(Value, window);
	CurrentGUI->SetCurrentGUI(CurrentGUI);
}

GUIFunction::~GUIFunction()
{

}
