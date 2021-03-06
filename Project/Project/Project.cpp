// Assingment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Player.h"
#include "ContactListener.h"	//For collision detection
#include "Environment.h"	//For platform creation
#include "Weapons.h"
#include "Menu.h"	//For main menu
#include "Client.h"	//For
#include "Server.h"	//networking
#include "Audio.h"
#include <vector>

static const float SCALE = 30.0f;	

int main()
{
	bool wasButtonPressed = false;	//Boolean to check for multiple button presses
	bool startGame = true;			//Boolean to check if the "Start game" button has been pressed in the main menu
	b2Vec2 Gravity(0.0f, 9.0f);		//World and Gravity set-up
	b2World World(Gravity);
	Environment LowerPlatform;
	LowerPlatform.CreatePlatform(&World, 400.f, 560.f);	//Creating the ground and setting the position to be at the bottom-middle of the screen

	Audio backgroundMusic("audio.wav");
	backgroundMusic.loop(true);

	Player* player = new Player(&World, 100, 50);	//Creating the initial box for the server
	Player* player2 = new Player(&World, 700, 50);	//Creating the initial box for the client

	std::vector<Player*> buildings;		//Creating a vector of box for the server
	std::vector<Player*> buildings2;	//Creating a vector of box for the client
	buildings.push_back(player);		//Pushes the initial boxes to the buildings vector for the server
	buildings2.push_back(player2);		//Pushes the initial boxes to the buildings vector for the client

	//SET UP BACKGROUND IMAGE
	sf::Texture backgroundTex;
	backgroundTex.loadFromFile("BackgroundTall.png");
	sf::Sprite backgroundSprite;
	sf::Vector2u size = backgroundTex.getSize(); //Setting the size to be the same as the imported texture
	backgroundSprite.setTexture(backgroundTex);
	backgroundSprite.setOrigin(0, size.y / 2);
	//BACKGROUND IMAGE SET UP END

	//SETTING UP THE VIEWS
	sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 600.f)); //Setting the view to be the size of the game window
	view.setCenter(sf::Vector2f(400.f, 300.f)); //Setting the centre to be in the middle of the screen
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Game Window"); //Creating the render window
	sf::RenderWindow menuWindow(sf::VideoMode(800, 600, 32), "Main Menu");
	window.setView(view);
	//VIEW SET UP END
	Menu menu(menuWindow.getSize().x, menuWindow.getSize().y);
	bool isServer = false; bool isClient = false; //Check for whether the user is the client or the server

	backgroundMusic.Play();

	/*
	MAIN MENU
	Checks the states of buttons and calls the respective Menu class function, when a key is released to make sure the button cannot be held down
	*/
	while (menuWindow.isOpen())
	{
		menuWindow.draw(backgroundSprite);
		menu.Draw(menuWindow);
		sf::Event event;
		while (menuWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())//Checks, which of the menu buttons was pressed
					{
					case 0:				//Server button was pressed
						std::cout << "Server selected" << std::endl;
						isServer = true;
						menuWindow.close();						
						break;
					case 1:				//Client button was pressed
						std::cout << "Client selected" << std::endl;
						isClient = true;
						menuWindow.close();
						break;
					case 2:				//Exit game button was pressed
						menuWindow.close();
						window.close();
						break;
					}
					break;
				}
			}
		}
		menuWindow.display();
	}
	//MAIN MENU END

	ContactListener ContactListenerInstance;
	World.SetContactListener(&ContactListenerInstance);

	sf::Event event;

	//SET UP NETWORKING
	Server server;
	Client client;

	if (isServer)
	{
		sf::Packet HSPacket; //Creating the Hand-Shake packet
		server.bindPort(2000); //Setting the port to default to 2000
		server.connection(2000);
		HSPacket << player2->getCurrentPosX() << player2->getCurrentPosY(); //Sending the client location from the server's perspective to the client for initial set-up
		server.sendPacket(HSPacket); //Sending the prepared packet
		
	}

	if (isClient)
	{
		sf::Packet HSPacket; //Creating the Hand-Shake packet
		client.connect();
		while (client.receivePacket(HSPacket) == false) //Check if the client has received a packet 
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
		int x, y;
		HSPacket >> x >> y; //Setting the received coordinates to the client player character
		player2->SetPos(player->getCurrentPosX(), player->getCurrentPosY());
		player->SetPos(x, y);

	}

	sf::Clock networkTime;		//Creates a clock to track real-life time to depend on game ticks instead of framerate
	float tick = 60;
	float interval = 1 / tick;	//Calculating the interval 

	//NETWORKING SET UP END

	bool controllerSwitch = false;	//Boolean to check for individual user input for each window

	while (window.isOpen()) //Main game loop
	{

		window.setFramerateLimit(60);	//Limits the game to run at 60 frames per second
		World.Step(1 / 60.0f, 8, 3);	//(the length of the time passed to simulate (seconds), how strongly to correct velocity, how strongly to correct position)
		window.clear();
		window.draw(backgroundSprite);	//Draws the background image to the screen

		int i = buildings.size() - 1;	//Int for selecting the current box in buildings starting from 0 for the server
		int j = buildings2.size() - 1;	//Int for selecting the current box in buildings starting from 0 for the client
		bool networkUpdate = false;

		if (networkTime.getElapsedTime().asSeconds() >= interval)	//Checks if the time has passed is bigger than the interval
		{
			networkUpdate = true;									//If it is true, then send the packets and update the network
			networkTime.restart();									//Resets the real-life timer
		}
		/*
		Checking if the user is acting as a server or a client. If server - a packet is created and received with the X and Y
		coordinates for the current "player" object for the second player (in server's case it's the client) and sets the "player" object to be displayed
		at those coordinates.
		The same happens if the user is a client - however the second player in client's case is the server.
		*/
		if (isServer)
		{
			for (int k = 0; k < buildings2.size(); k++)
			{
				sf::Packet receivingServerPacket;
				if (server.receivePacket(receivingServerPacket))
				{
					int posX, posY;
					receivingServerPacket >> posX >> posY;
					buildings2[j]->SetPos(posX, posY);

				}
			}

		}
		if (isClient)
		{
			for (int k = 0; k < buildings2.size(); k++)
			{
				sf::Packet receivingClientPacket;
				if (client.receivePacket(receivingClientPacket))
				{
					int posX, posY;
					receivingClientPacket >> posX >> posY;
					buildings2[j]->SetPos(posX, posY);
				}
			}

		}

		while (window.pollEvent(event))
		{
			//Checks to see, which window is being focused between the client and the server windows
			if (event.type == sf::Event::GainedFocus)
			{
				controllerSwitch = true;
			}
			else if (event.type == sf::Event::LostFocus)
			{
				controllerSwitch = false;
			}
		}
		
		window.draw(buildings[i]->Draw("Building.png"));		//Draws the initial player objects to screen 
		window.draw(buildings2[j]->Draw("Building.png"));
		window.draw(LowerPlatform.Draw("Platform.png"));	//Draws the bottom platform to the screen
		menu.Draw(window);
		menu.objective(window);
		buildings[i]->startMovement();						//Starts the movement of the "building to be placed" to move from side to side
		bool isButtonPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space); //Boolean for checking if the Space key has been pressed
		if (controllerSwitch)	//Makes sure that the only the selected window (client or server) is being interacted with
		{
			if (isButtonPressed && !wasButtonPressed)	//Checks if the Space button was pressed and not held down
			{
				for (int i = buildings.size() - 1; i < buildings.size(); i++)
				{
					buildings[i]->release();		//Drops the current building and stops it's side-to-side movement
				}
			}
			if (!isButtonPressed && wasButtonPressed)
			{
				//Space button released
			}
			wasButtonPressed = isButtonPressed;	//Sets the boolean so the button cannot be held down
		}
		/*
		CURRENTLY NO ACTUAL FUNCTIONALITY
		Would be used, when the tower goes out of the screen - is too high
		Moves the users view upwards

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			view.move(0.f, -100.f);
			window.setView(view);
		}
		*/

		//Checks if the user is client or server, spawns another object relative to their starting positions, when the first one has collided with either another object
		//or the ground
		if (buildings[i]->SpawnNew() == true && isServer)
		{
			buildings.push_back(new Player(&World, 100, 50));
		}
		if (buildings[i]->SpawnNew() == true && isClient)
		{
			buildings.push_back(new Player(&World, 700, 50));
		}

		//Draws the newly spawned object to the screen along with all the previous ones
		for (int i = 0; i < buildings.size(); i++)
		{
			window.draw(buildings[i]->Draw("Building.png"));
		}

		World.DrawDebugData();

		//When the tick interval is smaller than the time passed the network is updated and new packets sent to both the server and the client
		if (networkUpdate == true)
		{
			//Both packets include the current positions of the buildings
			if (isServer)
			{

				for (int k = 0; k < buildings.size(); k++)
				{
					sf::Packet sendingServerPacket;
					sendingServerPacket << buildings[k]->getCurrentPosX() << buildings[k]->getCurrentPosY();
					server.sendPacket(sendingServerPacket);
				}



			}
			if (isClient)
			{

				for (int k = 0; k < buildings.size(); k++)
				{
					sf::Packet sendingClientPacket;
					sendingClientPacket << buildings[k]->getCurrentPosX() << buildings[k]->getCurrentPosY();
					client.sendPacket(sendingClientPacket);
				}

			}
		}

		
		window.display(); //Displays everything on screen
	}
	client.disconnect();
	server.disconnect();
	return 0;
}