#include "pch.h"
#include "Player.h"
#include <Box2D/Box2D.h>
static const float SCALE = 30.0f;

Player::Player(b2World* _World, int _x, int _y)
{

	HP = 100;
	World = _World;
	x = _x;
	y = _y;
	BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	BodyDef.type = b2_dynamicBody;
	body = World->CreateBody(&BodyDef);
	b2PolygonShape Shape;
	Shape.SetAsBox((64.f / 2) / SCALE, (56.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 5.0f;
	FixtureDef.shape = &Shape;
	body->CreateFixture(&FixtureDef);
	isFalling = false;
	body->SetUserData(this);
}
sf::Sprite Player::Draw(std::string TexturePath)
{
	PlayerTexture.loadFromFile(TexturePath);
	Sprite.setTexture(PlayerTexture);
	Sprite.setOrigin(32.f, 28.f);
	Sprite.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
	Sprite.setRotation(body->GetAngle() * 180 / b2_pi);

	return Sprite;
}
sf::Texture Player::getTexture()
{
	return PlayerTexture;
}
float Player::getPosX()
{
	return x / SCALE;
}
int Player::getCurrentPosY()
{
	return body->GetPosition().y;
}
int Player::getCurrentPosX()
{
	return body->GetPosition().x;
}
void Player::move(float _x, float _y)
{
	velocity = body->GetLinearVelocity();
	body->SetLinearVelocity(b2Vec2(velocity.x + _x, velocity.y + _y));
	std::cout << "Player move" << std::endl; 
}
void Player::jump(float impulseMultiplier)
{
	if(isContact == true)
	{
		impulse = body->GetMass() * impulseMultiplier;
		body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter(), true);
	}
	else
	{
		impulse = 0.0f;
		body->ApplyLinearImpulse(b2Vec2(0, 0), body->GetWorldCenter(), true);
	}
}
void Player::release()
{
	body->SetLinearVelocity(b2Vec2(0, 0));
	isFalling = true;
	if(isFalling == true)
	{
		body->ApplyLinearImpulse(b2Vec2(0, 10), body->GetWorldCenter(), true);
	
	}
}
void Player::startMovement()
{
	body->SetLinearVelocity(b2Vec2(0, 0));
	if(body->GetPosition().x != getPosX() + 2.0f && isMoving == true && isFalling == false)
	{
		body->ApplyForce(b2Vec2(0.0f, -36.f), body->GetWorldCenter(), true);
		body->SetLinearVelocity(b2Vec2(2.0f, 0.0f));
		
		if(body->GetPosition().x >= getPosX() + 2.0f)
		{
			isMoving = false;
		}
	}
	else if (body->GetPosition().x != getPosX() - 2.0f && isMoving == false && isFalling == false)
	{
		body->ApplyForce(b2Vec2(0.0f, -36.f), body->GetWorldCenter(), true);
		body->SetLinearVelocity(b2Vec2(-2.0f, 0.0f));

		if (body->GetPosition().x <= getPosX() - 2.0f)
		{
			isMoving = true;
		}
		
	}
}
bool Player::startContact()
{
	isContact = true;
	return isContact;
}
bool Player::endContact()
{
	isContact = false;
	return isContact;
}
bool Player::SpawnNew()
{
	bool spawn = false;
	if(isContact == true)
	{
		spawn = true;
		return spawn;
	}
}

void Player::getType()
{
	std::cout <<  "BUILDING TYPE : " << body->GetType() << std::endl;
}
void Player::setStatic()
{
	body->SetType(b2BodyType(b2_staticBody));
}

void Player::SetPos(int x, int y)
{
	body->SetTransform(b2Vec2(x, y), body->GetAngle());
}

sf::Packet& operator << (sf::Packet& packet, Player* player)
{
	return packet << player->getCurrentPosX() << player->getCurrentPosY();
}

sf::Packet& operator >> (sf::Packet& packet, Player* player)
{
	float posX, posY;
	packet >> posX >> posY;
	player->SetPos(posX, posY);
	return packet;
}
Player::~Player()
{
}
