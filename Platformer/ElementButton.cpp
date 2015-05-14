#include "ElementButton.h"

ElementButton::ElementButton() 
{
	
}

ElementButton::ElementButton(string Text, Vector2f Location, Vector2f Size, Color color, void(*ButtonFunction)())
{
	//Rect stuff
	this->ButtonFunction = ButtonFunction;
	this->PressColor = color;
	this->Location = Location;
	rect.setPosition(Location);
	rect.setSize(Size);
	rect.setFillColor(color);

	
	//Text Stuff (see how inconsistently I just capitalized "Stuff"?)
	font.loadFromFile("Fonts/AlegreyaSansSC-Light.otf");

	text.setFont(font);
	text.setColor(Color::Black);
}

ElementButton::~ElementButton()
{
	
}

void ElementButton::SetLocation(Vector2f Location)
{
	this->Location = Location;
	//rect.setOrigin(rect.getPosition().x + (rect.getSize().x / 2.0f), rect.getPosition().y + (rect.getSize().y / 2.0f));
	rect.setPosition(Location);

	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(Vector2f(Location.x + (rect.getSize().x / 3), Location.y + (rect.getSize().y / 3)));

	cout << "Set location of rect." << endl;
}

void ElementButton::SetLocation(Vector2f Location, Vector2u WindowDimensions)
{
	//rect.setOrigin(rect.getSize().x / 2.0f, rect.getSize().y / 2.0f);
	
	rect.setPosition(((Location.x / 100) * WindowDimensions.x) - Size.x / 2, ((Location.y / 100) * WindowDimensions.y) - (Size.y / 2));
	text.setPosition(((Location.x / 100) * WindowDimensions.x) - (Size.x / 2) + 5, ((Location.y / 100) * WindowDimensions.y)  /*(Size.y / 2)*/ - (text.getCharacterSize() / 1.3));
	cout << "Set location of rect." << endl;
}

void ElementButton::SetText(string TextA)
{
	font.loadFromFile("Fonts/AlegreyaSansSC-Light.otf");

	text.setFont(font);
	text.setColor(Color::Black);
	text.setString(TextA);
	cout << "Set text to '" << string(text.getString()) << "' for a new button." << endl;
}

void ElementButton::SetPressColor(Color color)
{
	this->PressColor = color;
	cout << "Set fill color of rect." << endl;
}

void ElementButton::SetPressTextColor(Color color)
{
	PressTextColor = color;
}

void ElementButton::SetTextColor(Color color)
{
	TextColor = color;
	text.setColor(color);
}

void ElementButton::SetInteriorColor(Color color)
{
	this->InteriorColor = color;
	rect.setFillColor(color);
}

void ElementButton::SetOutlineColor(Color color)
{
	rect.setOutlineThickness(2);
	OutlineColor = color;
	rect.setOutlineColor(color);
}

void ElementButton::SetSize(Vector2f Size)
{
	this->Size = Size;
	rect.setSize(Size);
	
	cout << "Set size of rect." << endl;
}

void ElementButton::SetFontSize(int FontSize)
{
	text.setCharacterSize(FontSize);
}

void ElementButton::PressButton()
{
	rect.setFillColor(PressColor);
	rect.setOutlineColor(PressColor);
	text.setColor(PressTextColor);
	IsPressed = true;
}

void ElementButton::SoftRelease()
{
	rect.setFillColor(InteriorColor);
	rect.setOutlineColor(OutlineColor);
	text.setColor(TextColor);

	IsPressed = false;
}

void ElementButton::ReleaseButton()
{
	rect.setFillColor(InteriorColor);
	rect.setOutlineColor(OutlineColor);
	text.setColor(TextColor);
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
	rect.setFillColor(OutlineColor);
}

void ElementButton::HoverRelease()
{
	rect.setFillColor(InteriorColor);
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

void ElementButton::Draw(RenderWindow* window)
{
	//cout << "This button's location is: " << this << endl;
	window->draw(rect);
	window->draw(text);
	//cout << "Drew button at " << rect.getPosition().x << ", " << rect.getPosition().y << endl;
}

Vector2f ElementButton::GetLocation()
{
	return rect.getPosition();
}