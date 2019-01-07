#pragma once
#include <SFML/Network.hpp>
class Client
{
public:
	Client();
	void connect();
	void sendPacket(sf::Packet &packet);
	bool receivePacket(sf::Packet &packet);
	void disconnect();
	~Client();

private:
	sf::TcpSocket socket;
	sf::Packet packet;
};

