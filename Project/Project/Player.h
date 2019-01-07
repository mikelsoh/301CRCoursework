#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
class Player
{

	int x, y;
	int HP, score;
	bool isContact, isStatContact;
	bool isMoving = true;
	bool isFalling = false;
	float impulse;
	sf::Texture PlayerTexture;
	sf::Sprite Sprite;
	b2Body* body;
	b2World* World;
	b2Vec2 velocity;
public:
	Player(b2World* _World, int _x, int _y);
	sf::Sprite Draw(std::string TexturePath);
	sf::Texture getTexture();
	float getPosX();
	int getCurrentPosY();

	int getCurrentPosX();

	void move(float _x, float _y);

	void jump(float impulse);

	void release();

	void startMovement();


	bool startContact();

	bool endContact();


	bool SpawnNew();


	void getType();

	void setStatic();

	void SetPos(int x, int y);

	~Player();
private:
	b2BodyDef BodyDef;
};

sf::Packet& operator << (sf::Packet& packet, Player* player);
sf::Packet& operator >> (sf::Packet& packet, Player* player);


