#include "pch.h"
#include "Audio.h"


Audio::Audio()
{
}

Audio::Audio(std::string audioname)
{
	sBuffer.loadFromFile(audioname);
	sSound.setBuffer(sBuffer);
}

void Audio::loop(bool state)
{
	sSound.setLoop(state);
}

void Audio::setVolume(float volume)
{
	sSound.setVolume(volume);
}

void Audio::Play()
{
	sSound.play();
}

Audio::~Audio()
{
}
