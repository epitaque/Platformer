#include "ElementButton.h"

// BUTTON CODE :D
ElementButton::ElementButton(string Text, Vector2f Location, Vector2f Size, Color color, void(*ButtonFunction)())
{
	//Rect stuff
	this->ButtonFunction = ButtonFunction;
	this->color = color;
	this->Location = Location;
	rect.setPosition(Location);
	rect.setSize(Size);
	rect.setFillColor(color);
	rect.setOutlineColor(Color(color.r + 60, color.g + 60, color.b + 60, color.a));
	
	//Text Stuff (see how inconsistently I just capitalized "Stuff"?)
	font.loadFromFile("Fonts/AlegreyaSansSC-Light.otf");
	text.setString(Text);
	text.setFont(font);
	text.setCharacterSize(Size.y / 1.5);
	text.setPosition(Location);
	text.setColor(Color::Black);
}

ElementButton::~ElementButton()
{
	
}

void ElementButton::PressButton()
{
	rect.setFillColor(Color(color.r + 59, color.g + 59, color.b + 59, color.a));
	IsPressed = true;
}

void ElementButton::SoftRelease()
{
	rect.setFillColor(color);
	IsPressed = false;
}

void ElementButton::ReleaseButton()
{
	rect.setFillColor(color);
	ButtonFunction();
	IsPressed = false;
}

void ElementButton::HoverButton()
{
	rect.setFillColor(Color(rect.getFillColor().r - 70, rect.getFillColor().g - 70, rect.getFillColor().b - 70, rect.getFillColor().a));
}

void ElementButton::HoverRelease()
{
	rect.setFillColor(color);
}

void ElementButton::Draw(RenderWindow* window)
{
	window->draw(rect);
	window->draw(text);
}

