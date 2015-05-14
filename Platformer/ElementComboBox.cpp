#include "ElementComboBox.h"

ElementComboBox::ElementComboBox(RenderWindow* window)
{
	this->window = window;
	ButtonStack.push_back(new ElementButton);
	cout << "Created a combobox!\n";
}

ElementComboBox::~ElementComboBox()
{
	for (int i = 0; i < ButtonStack.size(); i++)
		if (ButtonStack.at(i) != NULL)
			delete ButtonStack.at(i);
	if (window != NULL)
		delete window;
}

void ElementComboBox::Update()
{
	for (int i = 0; i < ButtonStack.size(); i++)
	{
		if (ButtonStack.at(i)->IsPressed) // Is the button being pressed?
		{								  // Yes
			cout << "Button " << i << " isPressed.\n";
			if (!Mouse::isButtonPressed(Mouse::Left)) // Is the mouse button not being pressed
			{										  // Yes
				if (Mouse::getPosition(*window).x > ButtonStack.at(i)->rect.getPosition().x && // Is the click inside of the button?
					Mouse::getPosition(*window).x < ButtonStack.at(i)->rect.getPosition().x + ButtonStack.at(i)->rect.getSize().x &&
					Mouse::getPosition(*window).y > ButtonStack.at(i)->rect.getPosition().y &&
					Mouse::getPosition(*window).y < ButtonStack.at(i)->rect.getPosition().y + ButtonStack.at(i)->rect.getSize().y)
				{																				// Yes
					cout << "Click is inside of the button.\n";
					ButtonStack.at(i)->ReleaseButton();	// Then release the button
					continue;
				}
				else
				{																				// No
					cout << "Click is not inside of the button. \n";
					cout << "Mouse.x of '" << Mouse::getPosition(*window).x << "' !> Button.rect.x of '" << ButtonStack.at(i)->rect.getPosition().x << "'\n";
					cout << "Mouse.x of '" << Mouse::getPosition(*window).x << "' !< Button.rect.x  + Button.rect.size.x of '" << ButtonStack.at(i)->rect.getPosition().x + ButtonStack.at(i)->rect.getSize().x << "'\n";
					cout << "Mouse.y of '" << Mouse::getPosition(*window).y << "' !< Button.rect.y of '" << ButtonStack.at(i)->rect.getPosition().y << "'\n";
					cout << "Mouse.y of '" << Mouse::getPosition(*window).y << "' !> Button.rect.y  + Button.rect.size.y of '" << ButtonStack.at(i)->rect.getPosition().y + ButtonStack.at(i)->rect.getSize().y << "'\n";


					ButtonStack.at(i)->SoftRelease(); // Soft release the button
					continue;
				}
			}
			else
			{								// No
				continue; // Do nothing
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Left) && // Is the mouse button being pressed? Yes
			Mouse::getPosition(*window).x > ButtonStack.at(i)->rect.getPosition().x && // Is the click is inside the button?
			Mouse::getPosition(*window).x < ButtonStack.at(i)->rect.getPosition().x + ButtonStack.at(i)->rect.getSize().x &&
			Mouse::getPosition(*window).y > ButtonStack.at(i)->rect.getPosition().y &&
			Mouse::getPosition(*window).y < ButtonStack.at(i)->rect.getPosition().y + ButtonStack.at(i)->rect.getSize().y)
		{																			// Yes
			ButtonStack.at(i)->PressButton(); // Press the button
			cout << "button has been pressed\n";
		}
	}
	if (!IsExpanded) //Combobox is not currently expanded
	{
		if (ButtonStack.front()->GetReleasedStatus())
		{
			cout << "Expanding ComboBox.\n";
			Expand();
		}
	}
	else //Combobox is expanded
	{
		for (int i = 0; i < ButtonStack.size(); i++)
		{
			if (ButtonStack.at(i)->GetReleasedStatus())
			{
				Vector2f BStackFrontCoords = ButtonStack.front()->GetLocation();
				cout << "BStackFrontCoords: " << BStackFrontCoords.x << ", " << BStackFrontCoords.y << endl;
				*ButtonStack.front() = *ButtonStack.at(i);
				ButtonStack.front()->SetLocation(BStackFrontCoords);
				Contract();
				break;
			}
		}
	}
	Draw(); 
}

void ElementComboBox::AddButton(ElementButton* ButtonA)
{
	cout << "Somethings right making the first button.\n";
	ButtonStack.back() = new ElementButton;
	*ButtonStack.front() = *ButtonA;
	cout << "Location of the button that was just made: " << ButtonStack.back() << endl;
}

void ElementComboBox::AddButton(string TextB)
{
	if (ButtonStack.at(0) == NULL)
	{
		cout << "Error while adding button; no template button to add buttons to.\n";
	}
	else
	{
		ButtonStack.push_back(new ElementButton);
		*ButtonStack.back() = *ButtonStack.front();
		ButtonStack.back()->SetText(TextB);  
		ButtonStack.back()->SetLocation(Vector2f(ButtonStack.front()->rect.getPosition().x, 
			ButtonStack.front()->rect.getPosition().y + (ButtonStack.front()->rect.getSize().y * (ButtonStack.size() - 1 )))); //Y Pos = the last element's y coordinate plus the first elements y size
		
		ButtonStack.back()->text.setCharacterSize(20);
		cout << "Text details of newly created button: \nSize = " << ButtonStack.back()->text.getCharacterSize() 
			<< " \nPosition = "	<< ButtonStack.back()->text.getPosition().x 
			<< ", " << ButtonStack.back()->text.getPosition().y << endl; 
		cout << "Y coord of newly added button: " << ButtonStack.back()->rect.getPosition().y << endl;
	}
}

void ElementComboBox::Draw()
{
	if (IsExpanded)
	{
		for (int i = 1; i < ButtonStack.size(); i++)
		{
			ButtonStack.at(i)->Draw(window);
		}
		ButtonStack.front()->Draw(window);
	}
	else
	{
		ButtonStack.front()->Draw(window);
	}
	
}

ElementButton* ElementComboBox::GetSelectedButton()
{
	return ButtonStack.front();
}

void ElementComboBox::Expand()
{
	IsExpanded = true;
}

void ElementComboBox::Contract()
{
	IsExpanded = false;
}