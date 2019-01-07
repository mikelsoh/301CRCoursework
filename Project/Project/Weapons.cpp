#include "pch.h"
#include "Weapons.h"

static const float SCALE = 30.0f;

Weapons::Weapons()
{
}
void Weapons::CreateSpear(b2World* _World, int _x, int _y)
{
	World = _World;
	x = _x;
	y = _y;
	power = 10;
	isMeele = true;
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	BodyDef.type = b2_dynamicBody;
	wep = World->CreateBody(&BodyDef);
	b2PolygonShape Shape;
	Shape.SetAsBox((64.f / 2) / SCALE, (16.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	wep->CreateFixture(&FixtureDef);

	wep->SetUserData(this);
}
sf::Sprite Weapons::Draw(std::string TexturePath)
{
	WeaponTexture.loadFromFile(TexturePath);
	Sprite.setTexture(WeaponTexture);
	Sprite.setOrigin(32.f, 8.f);
	Sprite.setPosition(SCALE * wep->GetPosition().x, SCALE * wep->GetPosition().y);
	Sprite.setRotation(wep->GetAngle() * 180 / b2_pi);

	return Sprite;
}
void Weapons::PickUp()
{

}

Weapons::~Weapons()
{
}
