#include "HUD.h"

HUD::HUD(sf::RenderWindow& window, EntityHandler& e) : e(e), window(window) {
	if(!mainFont.loadFromFile("fonts/mainFont.ttf")) {
		throw "[mainFont.ttf] could not be loaded";
	}
}

HUD::~HUD() {
	
}

void HUD::startTime() {
	timer.start();
}

void HUD::stopTime() {
	timer.stop();
}

void HUD::pauseTime() {
	timer.pause();
}

void HUD::resumeTime() {
	timer.resume();
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
	if(player->isPlayerOne()) {
		double healthFactor = player->getHealth() / cMaxHealth;

		sf::RectangleShape healthRedBordered;
		sf::RectangleShape healthGreenUnbordered;

		healthRedBordered.setPosition(sf::Vector2f(10, 10));
		healthRedBordered.setSize(sf::Vector2f(Window::WIDTH / 3, 64));
		healthRedBordered.setFillColor(sf::Color::Red);
		healthRedBordered.setOutlineColor(sf::Color::White);
		healthRedBordered.setOutlineThickness(3);

		healthGreenUnbordered.setPosition(sf::Vector2f(10, 10));
		healthGreenUnbordered.setSize(sf::Vector2f((Window::WIDTH / 3) * healthFactor, 64));
		healthGreenUnbordered.setFillColor(sf::Color::Green);

		window.draw(healthRedBordered);
		if(player->getHealth() < 1)
			return;
		window.draw(healthGreenUnbordered);
	}
}

void HUD::renderTimer() {
	std::string time = formatTime(timer.getElapsedMilliseconds());

	
	sf::Text text(time, mainFont, 30);
	text.setPosition(Window::WIDTH / 2 - text.getGlobalBounds().width / 2, 5);

	window.draw(text);
}

void HUD::renderShopAccess() {

}

void HUD::renderPauseAccess() {

}