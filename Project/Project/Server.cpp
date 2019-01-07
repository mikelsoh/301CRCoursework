#include "pch.h"
#include "Server.h"


Server::Server()
{
}

void Server::bindPort(int port)
{
	listener.listen(port);
}

void Server::connection(int port)
{
	if(listener.listen(port) != sf::Socket::Done)
	{
		//handle error
	}
	if(listener.accept(socket) != sf::Socket::Done)
	{
		//handle error
	}
	socket.setBlocking(false);
}

int Server::checkPort()
{
	return socket.getRemotePort();
}

void Server::sendPacket(sf::Packet &packet)
{
	socket.send(packet);
}

bool Server::receivePacket(sf::Packet &packet)
{
	if(socket.receive(packet) == sf::Socket::Status::Done)
	{
		return true;
	}
	return false;
}
void Server::disconnect()
{
	socket.disconnect();
}
Server::~Server()
{
}
