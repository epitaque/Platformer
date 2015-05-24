#include "ElementButton.h"

ElementButton::ElementButton() 
{
	AnimationDuration = 300;
}

ElementButton::~ElementButton()
{
	
}

void ElementButton::SetLocation(Vector2f Location)
{
	this->Location = Location;
	//rect.SetOrigin(rect.getPosition().x + (rect.getSize().x / 2.0f), rect.getPosition().y + (rect.getSize().y / 2.0f));
	rect.setPosition(Location);

	FloatRect textRect = Text.getLocalBounds();
	Text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	Text.setPosition(Vector2f(Location.x + (rect.getSize().x / 3), Location.y + (rect.getSize().y / 3)));

	cout << "Set location of rect." << endl;
}

void ElementButton::SetLocation(Vector2f Location, Vector2u WindowDimensions)
{
	//rect.SetOrigin(rect.getSize().x / 2.0f, rect.getSize().y / 2.0f);
	
	rect.setPosition(((Location.x / 100) * WindowDimensions.x) - (Size.x / 2), ((Location.y / 100) * WindowDimensions.y) - (Size.y / 2));
	Text.setPosition(((Location.x / 100) * WindowDimensions.x) - (Size.x / 2) + 5, ((Location.y / 100) * WindowDimensions.y)  /*(Size.y / 2)*/ - (Text.getCharacterSize() / 1.3));
	cout << "Set location of rect." << endl;
}

void ElementButton::SetText(string TextA)
{
	TextFont.loadFromFile("Fonts/AlegreyaSans-Medium.otf");
	//font.loadFromFile("arial.ttf");

	Text.setFont(TextFont);
	Text.setColor(Color::Black);
	Text.setString(TextA);
	cout << "Set text to '" << string(Text.getString()) << "' for a new button." << endl;
}

void ElementButton::SetOnClickColor(Color color)
{
	this->OnClickInteriorColor = color;
	cout << "Set fill color of rect." << endl;
}

void ElementButton::SetOnClickTextColor(Color color)
{
	OnClickTextColor = color;
}

void ElementButton::SetTextColor(Color color)
{
	TextColor = color;
	Text.setColor(color);
}

void ElementButton::SetInteriorColor(Color color)
{
	this->EndInteriorColor = color;
	rect.setFillColor(color);
}

void ElementButton::SetOutlineColor(Color color)
{
	rect.setOutlineThickness(1);
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
	Text.setCharacterSize(FontSize);
}

//
// Click-related functions
//---------------------------------
void ElementButton::OnClick()
{
	Clock.restart();
	
	IsReleased = false;

	StartInteriorColor = rect.getFillColor();
	EndInteriorColor = OnClickInteriorColor;
	StartTextColor = Text.getColor();
	EndTextColor = OnClickTextColor;

	IsClicked = true;
}

void ElementButton::OnSoftRelease()
{
	rect.setFillColor(InteriorColor);
	rect.setOutlineColor(OutlineColor);
	Text.setColor(TextColor);

	IsClicked = false;
}

void ElementButton::OnRelease()
{
	if (ButtonFunction != NULL)
	{
		ButtonFunction();
	}
	
	cout << "ButtonFunction!\n";

	IsClicked = false;
	IsHovered = false;

	StartInteriorColor = rect.getFillColor();
	EndInteriorColor = InteriorColor;

	StartTextColor = Text.getColor();
	EndTextColor = TextColor;


	IsReleased = true;
}

//
// Hover-related functions
//----------------------------------

void ElementButton::OnHover()
{
	if (!IsHovered)
	{
		IsHovered = true;
	}
}

void ElementButton::Draw(RenderWindow* window)
{
	//cout << "This button's location is: " << this << endl;
	window->draw(rect);
	window->draw(Text);
	//cout << "Drew button at " << rect.getPosition().x << ", " << rect.getPosition().y << endl;
}

//
// Color fading for the animation
//-----------------------------

void ElementButton::Update()
{
	if (IsClicked)
	{
		if (rect.getFillColor() != EndInteriorColor)
		{
			rect.setFillColor(StartInteriorColor + ((EndInteriorColor - StartInteriorColor) * (Clock.getElapsedTime().asMilliseconds / AnimationDuration)));
		}
	}
	else if (IsReleased)
	{
		if (rect.getFillColor == EndInteriorColor)
		{
			IsReleased = false;
		}
		else
		{
			rect.setFillColor(StartInteriorColor + ((EndInteriorColor - StartInteriorColor) * (Clock.getElapsedTime().asMilliseconds / AnimationDuration)));
		}
	}
	else if (IsHovered)
	{
		if (Text.getColor() != EndTextColor)
		{
			rect.setFillColor(StartInteriorColor + ((EndInteriorColor - StartInteriorColor) * (Clock.getElapsedTime().asMilliseconds / AnimationDuration)));
		}
	}
}