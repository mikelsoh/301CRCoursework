#include "pch.h"
#include "ContactListener.h"


ContactListener::ContactListener()
{
}
void ContactListener::BeginContact(b2Contact* Contact)
{
	b2Fixture* f1 = Contact->GetFixtureA();
	b2Fixture* f2 = Contact->GetFixtureB();

	b2Body* b1 = f1->GetBody();
	b2Body* b2 = f2->GetBody();

	Player* o1 = (Player*)b1->GetUserData();
	Player* o2 = (Player*)b2->GetUserData();

	if (o1)
	{
		static_cast<Player*>(o1)->startContact();
	}
	if (o2)
	{
		static_cast<Player*>(o2)->startContact();
	}
}
void ContactListener::EndContact(b2Contact* Contact)
{
	b2Fixture* f1 = Contact->GetFixtureA();
	b2Fixture* f2 = Contact->GetFixtureB();

	b2Body* b1 = f1->GetBody();
	b2Body* b2 = f2->GetBody();

	Player* o1 = (Player*)b1->GetUserData();
	Player* o2 = (Player*)b2->GetUserData();

	if (o1)
	{
		static_cast<Player*>(o1)->endContact();
	}
	if (o2)
	{
		static_cast<Player*>(o2)->endContact();
	}
}

ContactListener::~ContactListener()
{
}
