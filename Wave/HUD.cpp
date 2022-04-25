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
	renderHealth(&e.entities);

	renderTimer();
	renderShopAccess();
	renderPauseAccess();
}

void HUD::renderHealth(std::vector<Entity*>* entities) {
	PlayerEntity* player1 = nullptr;
	PlayerEntity* player2 = nullptr;

	for(int i = 0; i < entities->size(); i++) {
		if(entities->at(i)->getId() == ID::Player) {
			PlayerEntity* p = (PlayerEntity*) entities->at(i);
			if(p->isPlayerOne()) {
				player1 = p;
			} else {
				player2 = p;
			}
		}
	}

	sf::RectangleShape healthRedBorderedP1;
	sf::RectangleShape healthGreenUnborderedP1;

	if(player1 != nullptr) {
		double healthFactorP1 = player1->getHealth() / cMaxHealth;

		healthRedBorderedP1.setPosition(sf::Vector2f(10, 10));
		healthRedBorderedP1.setSize(sf::Vector2f(Window::WIDTH / 3, 64));
		healthRedBorderedP1.setFillColor(sf::Color::Red);
		healthRedBorderedP1.setOutlineColor(sf::Color::White);
		healthRedBorderedP1.setOutlineThickness(3);

		healthGreenUnborderedP1.setPosition(sf::Vector2f(10, 10));
		healthGreenUnborderedP1.setSize(sf::Vector2f((Window::WIDTH / 3) * healthFactorP1, 64));
		healthGreenUnborderedP1.setFillColor(sf::Color::Green);
	}

	if(player2 != nullptr) {
		if(player2->getBounds().getGlobalBounds().intersects(healthRedBorderedP1.getGlobalBounds())) {
			healthGreenUnborderedP1.setFillColor(sf::Color(healthGreenUnborderedP1.getFillColor().r, healthGreenUnborderedP1.getFillColor().g, healthGreenUnborderedP1.getFillColor().b, healthGreenUnborderedP1.getFillColor().a / 2));
			healthGreenUnborderedP1.setOutlineColor(sf::Color(healthGreenUnborderedP1.getOutlineColor().r, healthGreenUnborderedP1.getOutlineColor().g, healthGreenUnborderedP1.getOutlineColor().b, healthGreenUnborderedP1.getOutlineColor().a / 2));
			healthRedBorderedP1.setFillColor(sf::Color(healthRedBorderedP1.getFillColor().r, healthRedBorderedP1.getFillColor().g, healthRedBorderedP1.getFillColor().b, healthRedBorderedP1.getFillColor().a / 2));
			healthRedBorderedP1.setOutlineColor(sf::Color(healthRedBorderedP1.getOutlineColor().r, healthRedBorderedP1.getOutlineColor().g, healthRedBorderedP1.getOutlineColor().b, healthRedBorderedP1.getOutlineColor().a / 2));
		}
	}

	if(player1 != nullptr) {
		if(player1->getBounds().getGlobalBounds().intersects(healthRedBorderedP1.getGlobalBounds())) {
			healthGreenUnborderedP1.setFillColor(sf::Color(healthGreenUnborderedP1.getFillColor().r, healthGreenUnborderedP1.getFillColor().g, healthGreenUnborderedP1.getFillColor().b, healthGreenUnborderedP1.getFillColor().a / 2));
			healthGreenUnborderedP1.setOutlineColor(sf::Color(healthGreenUnborderedP1.getOutlineColor().r, healthGreenUnborderedP1.getOutlineColor().g, healthGreenUnborderedP1.getOutlineColor().b, healthGreenUnborderedP1.getOutlineColor().a / 2));
			healthRedBorderedP1.setFillColor(sf::Color(healthRedBorderedP1.getFillColor().r, healthRedBorderedP1.getFillColor().g, healthRedBorderedP1.getFillColor().b, healthRedBorderedP1.getFillColor().a / 2));
			healthRedBorderedP1.setOutlineColor(sf::Color(healthRedBorderedP1.getOutlineColor().r, healthRedBorderedP1.getOutlineColor().g, healthRedBorderedP1.getOutlineColor().b, healthRedBorderedP1.getOutlineColor().a / 2));
		}
	}

	window.draw(healthRedBorderedP1);

	if(player1 != nullptr)
		if(player1->getHealth() > 1)
			window.draw(healthGreenUnborderedP1);

	if(player2 != nullptr) {
		sf::Text playerMarkerP1("P1 [White]", mainFont, 22);
		playerMarkerP1.setPosition(13, 13);
		playerMarkerP1.setFillColor(sf::Color::White);
		playerMarkerP1.setOutlineColor(sf::Color::Black);
		playerMarkerP1.setOutlineThickness(2.0f);

		window.draw(playerMarkerP1);

		double healthFactorP2 = player2->getHealth() / cMaxHealth;

		sf::RectangleShape healthRedBorderedP2;
		sf::RectangleShape healthGreenUnborderedP2;

		healthRedBorderedP2.setPosition(sf::Vector2f(Window::WIDTH - Window::WIDTH / 3 - 10, 10));
		healthRedBorderedP2.setSize(sf::Vector2f(Window::WIDTH / 3, 64));
		healthRedBorderedP2.setFillColor(sf::Color::Red);
		healthRedBorderedP2.setOutlineColor(sf::Color::White);
		healthRedBorderedP2.setOutlineThickness(3);

		healthGreenUnborderedP2.setPosition(sf::Vector2f(Window::WIDTH - Window::WIDTH / 3 - 10, 10));
		healthGreenUnborderedP2.setSize(sf::Vector2f((Window::WIDTH / 3) * healthFactorP2, 64));
		healthGreenUnborderedP2.setFillColor(sf::Color::Green);

		if(player1 != nullptr) {
			if(player1->getBounds().getGlobalBounds().intersects(healthRedBorderedP2.getGlobalBounds()) || player2->getBounds().getGlobalBounds().intersects(healthRedBorderedP2.getGlobalBounds())) {
				healthGreenUnborderedP2.setFillColor(sf::Color(healthGreenUnborderedP2.getFillColor().r, healthGreenUnborderedP2.getFillColor().g, healthGreenUnborderedP2.getFillColor().b, healthGreenUnborderedP2.getFillColor().a / 2));
				healthGreenUnborderedP2.setOutlineColor(sf::Color(healthGreenUnborderedP2.getOutlineColor().r, healthGreenUnborderedP2.getOutlineColor().g, healthGreenUnborderedP2.getOutlineColor().b, healthGreenUnborderedP2.getOutlineColor().a / 2));
				healthRedBorderedP2.setFillColor(sf::Color(healthRedBorderedP2.getFillColor().r, healthRedBorderedP2.getFillColor().g, healthRedBorderedP2.getFillColor().b, healthRedBorderedP2.getFillColor().a / 2));
				healthRedBorderedP2.setOutlineColor(sf::Color(healthRedBorderedP2.getOutlineColor().r, healthRedBorderedP2.getOutlineColor().g, healthRedBorderedP2.getOutlineColor().b, healthRedBorderedP2.getOutlineColor().a / 2));
			}
		}

		window.draw(healthRedBorderedP2);

		if(player2->getHealth() > 1)
			window.draw(healthGreenUnborderedP2);

		sf::Text playerMarkerP2("P2 [Pink]", mainFont, 22);
		playerMarkerP2.setPosition(Window::WIDTH - playerMarkerP2.getGlobalBounds().width - 13, 13);
		playerMarkerP2.setFillColor(sf::Color::White);
		playerMarkerP2.setOutlineColor(sf::Color::Black);
		playerMarkerP2.setOutlineThickness(2.0f);

		window.draw(playerMarkerP2);
	}
}

void HUD::renderTimer() {
	std::string time = formatTime(timer.getElapsedMilliseconds());

	
	sf::Text timeText(time, mainFont, 30);
	timeText.setPosition((int32_t) (Window::WIDTH / 2 - timeText.getGlobalBounds().width / 2), 5);
	timeText.setOutlineColor(sf::Color::Black);
	timeText.setOutlineThickness(2.0f);

	window.draw(timeText);
}

void HUD::renderShopAccess() {

}

void HUD::renderPauseAccess() {

}