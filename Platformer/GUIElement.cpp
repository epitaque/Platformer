#include "GUIElement.h"


GUIElement::GUIElement(string Text, Vector2f Location, string Type)
{
	this->Text = Text;
	this->Location = Location;
	this->Text = Text;
}
void GUIElement::CreateElement()
{
	if (this->Type == "Button")
	{
		Button = new GUIElementButton(Text, Location, Size, color, ButtonFunction);
	}
	else if (this->Type == "ComboBox")
	{
		//ComboBox = new GUIElementComboBox(Text, Position);
	}
	else if (this->Type == "TextField")
	{

	}
	else
	{
		cout << "Unknown GUIElement type!";
	}
}
void GUIElement::MousePressed()
{
	if (Type == "Button")
	{

	}
	else if (Type == "ComboBox")
	{

	}
}
void GUIElement::MouseReleased()
{
	IsPressed = false;
}
void GUIElement::MouseHovered()
{

}
void GUIElement::SoftRelease()
{
	IsPressed = false;
}

GUIElement::~GUIElement()
{
}
