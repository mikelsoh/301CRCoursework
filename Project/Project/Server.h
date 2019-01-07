#pragma once
#include <SFML/Network.hpp>

class Server
{
public:
	Server();
	void bindPort(int port);
	void connection(int port);
	int checkPort();
	void sendPacket(sf::Packet &packet);
	bool receivePacket(sf::Packet &packet);
	void disconnect();
	~Server();
	
private:
	sf::TcpSocket socket;
	sf::TcpListener listener;
	sf::Packet packet;
};

