#pragma once
#include <SFML/Graphics.hpp>

#define MAX_ITEMS 3


class Menu
{
public:
	Menu(float width, float height);

	void Draw(sf::RenderWindow &window);
	int GetPressedItem() { return selectedItemIndex; }
	void MoveUp();
	void MoveDown();

	void objective(sf::RenderWindow &window);


	~Menu();
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];

};

