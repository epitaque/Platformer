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

	
	//Text Stuff (see how inconsistently I just capitalized "Stuff"?)
	font.loadFromFile("Fonts/AlegreyaSansSC-Light.otf");

	text.setFont(font);
	text.setCharacterSize(Size.y / 1.5);
	text.setColor(Color::Black);
}

ElementButton::~ElementButton()
{
	
}

void ElementButton::SetLocation(Vector2f Location, Vector2u WindowDimensions)
{
	rect.setPosition(((Location.x / 100) * WindowDimensions.x) - Size.x / 2, ((Location.y / 100) * WindowDimensions.y) - (Size.y / 2));
	text.setPosition(((Location.x / 100) * WindowDimensions.x) - (Size.x / 2) + 5, ((Location.y / 100) * WindowDimensions.y)  /*(Size.y / 2)*/ - (text.getCharacterSize() / 1.3));
	cout << "Set location of rect." << endl;
}

void ElementButton::SetText(string TextA)
{
	cout << "Setting text...\n";
	font.loadFromFile("Fonts/AlegreyaSansSC-Light.otf");
	cout << "Font: " << font.getInfo().family << endl;

	text.setFont(font);
	text.setColor(Color::Black);
	text.setString(TextA);
	cout << "Set text to " << TextA << endl;
}

void ElementButton::SetColor(Color color)
{
	this->color = color;
	rect.setFillColor(color);
	rect.setOutlineColor(Color(color.r - 20, color.g - 20, color.b - 20, color.a));
	rect.setOutlineThickness(4);
	cout << "Set fill color of rect." << endl;
}

bool ElementButton::GetReleasedStatus()
{
	if (IsReleased)
	{
		IsReleased = false;
		return true;
	}
	else
	{
		return false;
	}
}

void ElementButton::SetSize(Vector2f Size)
{
	this->Size = Size;
	rect.setSize(Size);
	text.setCharacterSize( (rect.getSize().x / text.getString().getSize() ) + 10);
	cout << "Set size of rect." << endl;
}
void ElementButton::PressButton()
{
	rect.setFillColor(Color(color.r - 19, color.g - 19, color.b - 19, color.a));
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
	if (ButtonFunction != NULL)
	{
		ButtonFunction();
	}
	IsReleased = true;
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

