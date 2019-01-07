#include "pch.h"
#include "Environment.h"
static const float SCALE = 30.0f;

Environment::Environment()
{
}

void Environment::CreatePlatform(b2World* _World, int _x, int _y)
{
	World = _World;
	x = _x;
	y = _y;
	b2BodyDef PlatformDef;
	PlatformDef.position = b2Vec2(x / SCALE, y / SCALE);
	PlatformDef.type = b2_staticBody;
	Platform = World->CreateBody(&PlatformDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.f / 2) / SCALE, (15.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Platform->CreateFixture(&FixtureDef);
	Platform->SetUserData(this);
}

sf::Sprite Environment::Draw(std::string path)
{
	PlatformTexture.loadFromFile(path);
	PlatformSprite.setTexture(PlatformTexture);
	PlatformSprite.setOrigin(400.f, 8.f);
	PlatformSprite.setPosition(Platform->GetPosition().x * SCALE, Platform->GetPosition().y * SCALE);
	PlatformSprite.setRotation(180 / b2_pi * Platform->GetAngle());
	
	return PlatformSprite;	
}
void Environment::getType()
{
	std::cout << "ENVIRONMENT TYPE: " << Platform->GetType() << std::endl;
}

Environment::~Environment()
{
}
