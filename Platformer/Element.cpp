#include "Element.h"
#include "GUITempReplacer.h"
#include "GUI.h"

using namespace std;

Element::Element()
{
	
}

void Element::SetCurrentGUI(GUI* CurrentGUI)
{
	//cout << CurrentGUI;
	
	this->CurrentGUI = CurrentGUI;
	//cout << "Element.cpp outsidewindow: " << CurrentGUI->window << endl;
	//cout << "Element.cpp insidewindow: " << this->CurrentGUI->window << endl;

}

void Element::ExecuteFunction(string Type, string Value)
{
	if (Type == "ReplaceGUI")
	{
		cout << "Switching GUIs...\n";
		cout << "Value = " << Value << endl;
		ReplaceGUI(Value);
	}
	else
	{
		cout << "Unknown function\n";
	}
}

void Element::ReplaceGUI(string Value)
{
	GUITempReplacer(Value, CurrentGUI->window, CurrentGUI);
}

Element::~Element()
{
	cout << "Element destructor called.\n";
}
