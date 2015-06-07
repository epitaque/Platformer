#include "ElementButton.h"

ElementButton::ElementButton() 
{
	AnimationDuration = 300;
	TextFont = new Font;
}

ElementButton::~ElementButton()
{
	cout << "Button destructor called.\n";
}

//
// Attribute changing functions used in parsing
//----------------------------------------------------

void ElementButton::SetLocation(Vector2f Location)
{
	this->Location = Location;
	//rect.SetOrigin(rect.getPosition().x + (rect.getSize().x / 2.0f), rect.getPosition().y + (rect.getSize().y / 2.0f));
	rect.setPosition(Location);

	FloatRect textRect = Text.getLocalBounds();
	Text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	Text.setPosition(Vector2f(Location.x + (rect.getSize().x / 3), Location.y + (rect.getSize().y / 3)));

}

void ElementButton::SetLocation(Vector2f Location, Vector2u WindowDimensions)
{
	//rect.SetOrigin(rect.getSize().x / 2.0f, rect.getSize().y / 2.0f);
	
	rect.setPosition(((Location.x / 100) * WindowDimensions.x) - (Size.x / 2), ((Location.y / 100) * WindowDimensions.y) - (Size.y / 2));
	Text.setPosition(((Location.x / 100) * WindowDimensions.x) - (Size.x / 2) + 5, ((Location.y / 100) * WindowDimensions.y)  /*(Size.y / 2)*/ - (Text.getCharacterSize() / 1.3));
}

void ElementButton::SetText(string TextA)
{
	TextFont->loadFromFile("Fonts/AlegreyaSans-Medium.otf");
	//font.loadFromFile("arial.ttf");

	Text.setFont(*TextFont);
	Text.setColor(Color::Black);
	Text.setString(TextA);
	//cout << "Set text to '" << string(Text.getString()) << "' for a new button." << endl;
}

void ElementButton::SetOnClickInteriorColor(Color color)
{
	this->OnClickInteriorColor = color;
}

void ElementButton::SetOnHoverInteriorColor(Color color)
{
	OnHoverInteriorColor = color;
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
	this->InteriorColor = color;
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
	
	//cout << "Set size of rect." << endl;
}

void ElementButton::SetFontSize(int FontSize)
{
	Text.setCharacterSize(FontSize);
}

void ElementButton::SetFunction(string Type, string Value)
{
	FunctionType = Type;
	FunctionValue = Value;
}

//
// Click-related functions
//---------------------------------
void ElementButton::OnClick()
{
	cout << "Button clicked.\n";
	Clock.restart();
	
	IsSoftReleased = false;
	IsReleased = false;

	StartInteriorColor = rect.getFillColor();
	EndInteriorColor = OnClickInteriorColor;

	StartTextColor = Text.getColor();
	EndTextColor = OnClickTextColor;

	IsClicked = true;
}

void ElementButton::OnSoftRelease()
{

	if (IsClicked || IsHovered)
	{
		cout << "Button SoftReleased.\n";
		Clock.restart();

		StartInteriorColor = Color(rect.getFillColor());
		EndInteriorColor = InteriorColor;

		IsSoftReleased = true;
		IsClicked = false;
		IsHovered = false;

		StartTextColor = Text.getColor();
		EndTextColor = TextColor;
	}
	
}

void ElementButton::OnRelease()
{
	if (FunctionType != "")
	{
		ExecuteFunctionB();
	}
	else
	{
		cout << "No function to execute!\n";
	}

	cout << "Button released.\n";

	Clock.restart();

	IsClicked = false;
	IsHovered = false;
	IsSoftReleased = false;
	IsReleased = true;

	StartInteriorColor = rect.getFillColor();
	EndInteriorColor = InteriorColor;

	StartTextColor = Text.getColor();
	EndTextColor = TextColor;

}

void ElementButton::ExecuteFunctionB()
{
	ExecuteFunction(FunctionType, FunctionValue);
}

//
// Hover-related functions
//----------------------------------

void ElementButton::OnHover()
{
	
	if (!IsClicked && !IsHovered)
	{
		cout << "Button hovered.\n";

		Clock.restart();

		IsHovered = true;
		StartInteriorColor = rect.getFillColor();
		EndInteriorColor = OnHoverInteriorColor;
	}
	
	IsSoftReleased = false;
}

void ElementButton::Draw(RenderWindow* Window)
{
	//cout << "This button's location is: " << this << endl;
	//cout << "Drawing rect for button. rect address = " << &rect << endl;
	Window->draw(rect);
	Window->draw(Text);
	//cout << "Drew button at " << rect.getPosition().x << ", " << rect.getPosition().y << endl;
}

//
// Color fading for the different animations.
//---------------------------------

void ElementButton::Update(RenderWindow* Window)
{
	if (float(Clock.getElapsedTime().asMilliseconds() / AnimationDuration) < 1)
	{
		TimePercent = Clock.getElapsedTime().asMilliseconds() / AnimationDuration;
		//cout << "Updating TimePercent. TimePercent = " << Clock.getElapsedTime().asMilliseconds() / AnimationDuration << endl;
		//cout << "Elapsed milliseconds: '" << Clock.getElapsedTime().asMilliseconds() << "' \n";
	}
	else
	{
		TimePercent = 1;
	}

	/*if (Color(rect.getFillColor()) != EndInteriorColor)
	{
		AnimateFadeInterior();
	}
	if (Color(Text.getColor()) != EndTextColor)
	{
		AnimateFadeText();
	}*/
	
	if (IsClicked)
	{
		if (Color(rect.getFillColor()) != EndInteriorColor)
		{	
			AnimateFadeInterior();

			AnimateFadeText();
		}
	}
	else if (IsReleased)
	{
		if (Color(rect.getFillColor()) == EndInteriorColor)
		{
			IsReleased = false;
		}
		else
		{
			AnimateFadeInterior();
			
			AnimateFadeText();
		}
	}
	else if (IsSoftReleased)
	{
		if (Color(rect.getFillColor()) == EndInteriorColor)
		{
			IsSoftReleased = false;
		}
		else
		{
			AnimateFadeInterior();

			AnimateFadeText();
		}
	}
	else if (IsHovered)
	{
		if (Color(rect.getFillColor()) == EndInteriorColor)
		{
			
		}
		else
		{
			AnimateFadeInterior();
		}
	} 
	Draw(Window);
}

void ElementButton::AnimateFadeInterior()
{
	TempColor.r = (StartInteriorColor.r + (EndInteriorColor.r - StartInteriorColor.r)) * TimePercent;
	TempColor.b = (StartInteriorColor.b + (EndInteriorColor.b - StartInteriorColor.b)) * TimePercent;
	TempColor.g = (StartInteriorColor.g + (EndInteriorColor.g - StartInteriorColor.g)) * TimePercent;
	TempColor.a = (StartInteriorColor.a + (EndInteriorColor.a - StartInteriorColor.a)) * TimePercent;
	rect.setFillColor(TempColor);
}

void ElementButton::AnimateFadeText()
{
	TempColor.r = (StartTextColor.r + (EndTextColor.r - StartTextColor.r)) * TimePercent;
	TempColor.b = (StartTextColor.b + (EndTextColor.b - StartTextColor.b)) * TimePercent;
	TempColor.g = (StartTextColor.g + (EndTextColor.g - StartTextColor.g)) * TimePercent;
	TempColor.a = (StartTextColor.a + (EndTextColor.a - StartTextColor.a)) * TimePercent;
	Text.setColor(TempColor);
}