#include "Element.h"
#include "GUI.h"

using namespace std;

Element::Element()
{
	
}

void Element::SetCurrentGUI(GUI* CurrentGUI)
{
	//cout << CurrentGUI;
	
	this->CurrentGUI = CurrentGUI;
	WindowA = CurrentGUI->window;

}

void Element::ExecuteFunction(string Type, string Value)
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

void Element::ReplaceGUI(string Value)
{
	//cout << CurrentGUI->window << endl;
	CurrentGUI->~GUI();
	CurrentGUI = new GUI(Value, WindowA);
	CurrentGUI->SetCurrentGUI(CurrentGUI);
}

Element::~Element()
{

}
