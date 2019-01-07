#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Weapons
{
	b2World* World;
	b2Body* wep;
	sf::Texture WeaponTexture;
	sf::Sprite Sprite;
	int x, y;
	int power;
	bool isMeele;
	int index;

public:
	Weapons();
	void CreateSpear(b2World* _World, int _x, int _y);
	sf::Sprite Draw(std::string TexturePath);
	void PickUp();
	~Weapons();
};

