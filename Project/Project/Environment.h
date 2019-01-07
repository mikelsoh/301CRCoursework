#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
class Environment
{
	int x, y;
	b2Body* Platform;
	b2World* World;
	sf::Sprite PlatformSprite;
	sf::Texture PlatformTexture;

public:
	std::vector<b2Body*> Platforms;
	Environment();
	void CreatePlatform(b2World* _World, int _x, int _y);
	sf::Sprite Draw(std::string path);
	void getType();
	~Environment();
};

