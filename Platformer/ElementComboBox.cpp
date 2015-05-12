#include "ElementComboBox.h"

ElementComboBox::ElementComboBox(RenderWindow* window)
{
	this->window = window;
}

ElementComboBox::~ElementComboBox()
{
	for (int i = 0; i < ButtonStack.size(); i++)
		if (ButtonStack.at(i) != NULL)
			delete ButtonStack.at(i);
	if (SelectedButton != NULL)
		delete SelectedButton;
	if (window != NULL)
		delete window;
}

void ElementComboBox::Update()
{
	if (!IsExpanded) //Combobox is not currently expanded
	{
		if (ButtonStack.front()->GetReleasedStatus())
		{
			Expand();
		}
	}
	else //Combobox is expanded
	{
		for (int i = 0; i < ButtonStack.size(); i++)
		{
			if (ButtonStack.at(i)->GetReleasedStatus)
			{
				SelectedButton = ButtonStack.at(i);
				Contract();
			}
		}
	}
}

void ElementComboBox::AddButton(ElementButton ButtonA)
{
	if (ButtonStack.at(0) == NULL)
	{
		ButtonStack.back() = new ElementButton;
		*ButtonStack.front() = ButtonA;
	}
	else
	{
		ButtonStack.push_back(new ElementButton);
		*ButtonStack.back() = ButtonA;
		ButtonStack.back()->SetLocation(Vector2f(ButtonStack.front()->rect.getPosition().x, //Anyone who is reading this - is this bad coding practice to have these ridiculously long arguments?
												 ButtonStack.at(ButtonStack.size() - 1)->rect.getPosition().y + ButtonStack.front()->rect.getSize().y),
												 window->getSize());
	}
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
	}
}

void ElementComboBox::Draw(ElementButton* ButtonA)
{
	if (IsExpanded)
	{
		for (int i = 1; i < ButtonStack.size(); i++)
		{
			ButtonStack.at(i)->Draw(window);
		}
		SelectedButton->Draw(window);
	}
	else
	{
		SelectedButton->Draw(window);
	}
		
}

ElementButton* ElementComboBox::GetSelectedButton()
{
	return SelectedButton;
}

void ElementComboBox::Expand()
{
	IsExpanded = true;
}

void ElementComboBox::Contract()
{
	IsExpanded = false;
}