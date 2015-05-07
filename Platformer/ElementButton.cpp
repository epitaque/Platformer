#include "ElementButton.h"

ElementButton::ElementButton() 
{
}

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
	
	text.setFont(font);
	text.setCharacterSize(Size.y / 1.5);
	text.setColor(Color::Black);
}

ElementButton::~ElementButton()
{
	
}

void ElementButton::SetLocation(Vector2f Location, Vector2f WindowDimensions)
{
	rect.setPosition((Location.x / 100) * WindowDimensions.x, (Location.y / 100) * WindowDimensions.y);
	text.setPosition((Location.x / 100) * WindowDimensions.x, (Location.y / 100) * WindowDimensions.y);
	cout << "Set location of rect." << endl;
}

void ElementButton::SetText(string TextA)
{
	text.setString(TextA);
	cout << "Set text of rect." << endl;
}

void ElementButton::SetColor(Color color)
{
	this->color = color;
	rect.setFillColor(color);
	cout << "Set fill color of rect." << endl;
}


void ElementButton::SetSize(Vector2f Size)
{
	this->Size = Size;
	rect.setSize(Size);
	cout << "Set size of rect." << endl;
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
	//ButtonFunction();
	cout << "ButtonFunction!\n";
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
	//cout << "Drew button at " << rect.getPosition().x << ", " << rect.getPosition().y << endl;
}

