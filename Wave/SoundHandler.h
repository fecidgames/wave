#pragma once

#include <iostream>
#include <SFML/Audio.hpp>

class SoundHandler {
public:
	SoundHandler();

	void playMusic(int32_t id);
	void loopMusic(int32_t id);

	void updateVolume(int32_t volume);

private:
	sf::Music bgMusic;

};

