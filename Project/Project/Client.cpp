#include "pch.h"
#include "Client.h"


Client::Client()
{
}
void Client::connect()
{
	sf::Socket::Status status = socket.connect("127.0.0.1", 2000);
	if(status != sf::Socket::Done)
	{
		//handle error
	}
	socket.setBlocking(false);
}

void Client::sendPacket(sf::Packet &packet)
{
	socket.send(packet);
}

bool Client::receivePacket(sf::Packet &packet)
{
	if(socket.receive(packet) == sf::Socket::Status::Done)
	{
		return true;
	}
	return false;
}
void Client::disconnect()
{
	socket.disconnect();
}
Client::~Client()
{
}
