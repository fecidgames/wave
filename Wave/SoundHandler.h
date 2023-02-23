#pragma once

#include <iostream>
#include <SFML/Audio.hpp>

class SoundHandler {
public:
	SoundHandler();

	void playMusic(int32_t id);
	void loopMusic(int32_t id);
	void muteMusic(bool mute);

	void updateVolume(int32_t volume);

private:
	sf::Music bgMusic;
	int volume = 100;
	bool muted = false;

};

