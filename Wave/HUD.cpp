#include "HUD.h"

HUD::HUD(sf::RenderWindow& window, EntityHandler& entityHandler) : window(window), entityHandler(entityHandler) {

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
	for(Entity* e : entityHandler.entities) {
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
	formatTime(timer.getElapsedMilliseconds());
}

void HUD::renderShopAccess() {

}

void HUD::renderPauseAccess() {

}