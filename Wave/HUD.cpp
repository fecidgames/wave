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

	sf::Text hNotifyP1("", mainFont, 16);
	sf::Text hNotifyP2("", mainFont, 16);

	sf::RectangleShape hbRedP1;
	sf::RectangleShape huGreenP1;

	if(player1 != nullptr) {
		double healthFactorP1 = player1->getHealth() / cMaxHealth;

		hbRedP1.setPosition(sf::Vector2f(10, 10));
		hbRedP1.setSize(sf::Vector2f(1080 / 3, 64));
		hbRedP1.setFillColor(sf::Color::Red);
		hbRedP1.setOutlineColor(sf::Color::White);
		hbRedP1.setOutlineThickness(3);

		huGreenP1.setPosition(sf::Vector2f(10, 10));
		huGreenP1.setSize(sf::Vector2f((1080 / 3) * healthFactorP1, 64));
		huGreenP1.setFillColor(sf::Color::Green);

		hNotifyP1.setString(std::to_string(player1->getHealth()) + "/" + std::to_string(cMaxHealth));
		hNotifyP1.setOutlineColor(sf::Color::Black);
		hNotifyP1.setOutlineThickness(2.0f);
	}

	if(player2 != nullptr) {
		if(player2->getBounds().getGlobalBounds().intersects(hbRedP1.getGlobalBounds())) {
			huGreenP1.setFillColor(sf::Color(huGreenP1.getFillColor().r, huGreenP1.getFillColor().g, huGreenP1.getFillColor().b, huGreenP1.getFillColor().a / 2));
			huGreenP1.setOutlineColor(sf::Color(huGreenP1.getOutlineColor().r, huGreenP1.getOutlineColor().g, huGreenP1.getOutlineColor().b, huGreenP1.getOutlineColor().a / 2));

			hbRedP1.setFillColor(sf::Color(hbRedP1.getFillColor().r, hbRedP1.getFillColor().g, hbRedP1.getFillColor().b, hbRedP1.getFillColor().a / 2));
			hbRedP1.setOutlineColor(sf::Color(hbRedP1.getOutlineColor().r, hbRedP1.getOutlineColor().g, hbRedP1.getOutlineColor().b, hbRedP1.getOutlineColor().a / 2));
		}

		hNotifyP2.setString(std::to_string((int32_t) player2->getHealth()) + "/" + std::to_string((int32_t) cMaxHealth));
		hNotifyP2.setOutlineColor(sf::Color::Black);
		hNotifyP2.setOutlineThickness(2.0f);
	}

	if(player1 != nullptr) {
		if(player1->getBounds().getGlobalBounds().intersects(hbRedP1.getGlobalBounds())) {
			huGreenP1.setFillColor(sf::Color(huGreenP1.getFillColor().r, huGreenP1.getFillColor().g, huGreenP1.getFillColor().b, huGreenP1.getFillColor().a / 2));
			huGreenP1.setOutlineColor(sf::Color(huGreenP1.getOutlineColor().r, huGreenP1.getOutlineColor().g, huGreenP1.getOutlineColor().b, huGreenP1.getOutlineColor().a / 2));

			hbRedP1.setFillColor(sf::Color(hbRedP1.getFillColor().r, hbRedP1.getFillColor().g, hbRedP1.getFillColor().b, hbRedP1.getFillColor().a / 2));
			hbRedP1.setOutlineColor(sf::Color(hbRedP1.getOutlineColor().r, hbRedP1.getOutlineColor().g, hbRedP1.getOutlineColor().b, hbRedP1.getOutlineColor().a / 2));
		}
	}

	window.draw(hbRedP1);

	if(player1 != nullptr)
		if(player1->getHealth() > 1)
			window.draw(huGreenP1);

	hNotifyP1.setPosition(13, 25);

	if(player2 != nullptr) {
		sf::Text playerMarkerP1("P1 [White]", mainFont, 22);
		playerMarkerP1.setPosition(13, 13);
		playerMarkerP1.setFillColor(player1->getColor());
		playerMarkerP1.setOutlineColor(sf::Color::Black);
		playerMarkerP1.setOutlineThickness(2.0f);

		window.draw(playerMarkerP1);

		double healthFactorP2 = player2->getHealth() / cMaxHealth;

		sf::RectangleShape healthRedBorderedP2;
		sf::RectangleShape healthGreenUnborderedP2;

		healthRedBorderedP2.setPosition(sf::Vector2f(window.getSize().x - 1080 / 3 - 10, 10));
		healthRedBorderedP2.setSize(sf::Vector2f(1080 / 3, 64));
		healthRedBorderedP2.setFillColor(sf::Color::Red);
		healthRedBorderedP2.setOutlineColor(sf::Color::White);
		healthRedBorderedP2.setOutlineThickness(3);

		healthGreenUnborderedP2.setPosition(sf::Vector2f(window.getSize().x - 1080 / 3 - 10, 10));
		healthGreenUnborderedP2.setSize(sf::Vector2f((1080 / 3) * healthFactorP2, 64));
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
		playerMarkerP2.setPosition(window.getSize().x - playerMarkerP2.getGlobalBounds().width - 13, 13);
		playerMarkerP2.setFillColor(player2->getColor());
		playerMarkerP2.setOutlineColor(sf::Color::Black);
		playerMarkerP2.setOutlineThickness(2.0f);

		window.draw(playerMarkerP2);
	}
}

void HUD::renderTimer() {
	std::string time = formatTime(timer.getElapsedMilliseconds());

	sf::Text timeText(time, mainFont, 30);
	timeText.setPosition((int32_t) (window.getSize().x / 2 - timeText.getGlobalBounds().width / 2), 5);
	timeText.setOutlineColor(sf::Color::Black);
	timeText.setOutlineThickness(2.0f);

	window.draw(timeText);
}