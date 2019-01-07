#include "pch.h"
#include "Menu.h"


Menu::Menu(float width, float height)
{
	if(!font.loadFromFile("font.ttf"))
	{
		//error handle
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Server");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Client");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit game");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3));
}

void Menu::Draw(sf::RenderWindow &window)
{
	for(int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if(selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::objective(sf::RenderWindow &window)
{
	
	menu[0].setFillColor(sf::Color::Black);
	menu[0].setString("Build the highest tower!");
	menu[0].setPosition(window.getSize().x / 4, window.getSize().y / (MAX_ITEMS + 1) * 1);
	menu[0].setScale(0.5f, 0.5f);

	menu[1].setFillColor(sf::Color::Black);
	menu[1].setString("Press 'Space' to release");
	menu[1].setPosition(window.getSize().x / 4, window.getSize().y / (MAX_ITEMS + 1) * 1.5f);
	menu[1].setScale(0.5f, 0.5f);
	menu[2].setString("");
}

Menu::~Menu()
{
}
