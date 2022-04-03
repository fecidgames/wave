#include "HUD.h"

HUD::HUD(sf::RenderWindow& window, EntityHandler& e) : e(e), window(window) {
	
}

HUD::~HUD() {
	
}

void HUD::startTime() {
	timer.start();
}

void HUD::stopTime() {
	timer.stop();
}

void HUD::render() {
	for(Entity* e : e.entities) {
		if(e->getId() == ID::Player) {
			renderHealth((PlayerEntity*) e);
		}
	}

	renderTimer();
	renderShopAccess();
	renderPauseAccess();
}

void HUD::renderHealth(PlayerEntity* player) {

}

void HUD::renderTimer() {
	std::string time = formatTime(timer.getElapsedMilliseconds());

	sf::Font f;
	if(!f.loadFromFile("fonts/mainFont.ttf")) {
		throw "[mainFont.ttf] could not be loaded";
	}
	sf::Text text(time, f, 30);
	text.setPosition(Window::WIDTH / 2 - text.getGlobalBounds().width / 2, 5);

	window.draw(text);
}

void HUD::renderShopAccess() {

}

void HUD::renderPauseAccess() {

}