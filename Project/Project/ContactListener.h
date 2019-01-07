#pragma once
#include <Box2D/Box2D.h>
#include "Player.h"
#include "Weapons.h"
class ContactListener : public b2ContactListener
{
	b2Contact* Contact;
public:
	ContactListener();
	void BeginContact(b2Contact* Contact);
	void EndContact(b2Contact * Contact);
	~ContactListener();
};

