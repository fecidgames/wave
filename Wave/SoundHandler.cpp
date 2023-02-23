#include "SoundHandler.h"

SoundHandler::SoundHandler() {
	if(!bgMusic.openFromFile("sounds/Cheerfully Brainless.ogg"))
		std::cout << "[Cheerfully Brainless.ogg] could not be loaded\n";
}

void SoundHandler::playMusic(int32_t id) {
	if(id == 0) {
		bgMusic.play();
		return;
	}
}

void SoundHandler::loopMusic(int32_t id) {
	if(id == 0) {
		bgMusic.setLoop(!bgMusic.getLoop());
		return;
	}
}

void SoundHandler::muteMusic(bool mute) {
	muted = mute;
	bgMusic.setVolume((mute) ? 0 : volume);
}

void SoundHandler::updateVolume(int32_t volume) {
	this->volume = volume;
	if(!muted)
		bgMusic.setVolume(volume);
}
