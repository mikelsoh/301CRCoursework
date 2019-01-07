#pragma once

#include <SFML/Audio.hpp>

class Audio
{
private:
	sf::SoundBuffer sBuffer;
	sf::Sound sSound;
	
public:

	Audio();
	Audio(std::string audioname);

	void loop(bool state);

	void setVolume(float volume);

	void Play();

	~Audio();
};

