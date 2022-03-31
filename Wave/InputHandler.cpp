#include "InputHandler.h"

InputHandler::InputHandler(MenuRenderer& menuRenderer, EntityHandler& entityHandler) : menuRenderer(&menuRenderer), entityHandler(&entityHandler), gameState(menuRenderer.gameState) {

}

void InputHandler::update(sf::Event* e) {
	switch(e->type) {
		case sf::Event::MouseButtonPressed:
			for(Gui::Button* b : menuRenderer->getButtons()) {
				if(mouseOver((float_t) e->mouseButton.x, (float_t) e->mouseButton.y, b)) {
					b->down = true;
				}
			}

			break;

		case sf::Event::MouseButtonReleased:
			for(Gui::Button* b : menuRenderer->getButtons()) {
				b->down = false;

				if(mouseOver((float_t) e->mouseButton.x, (float_t) e->mouseButton.y, b)) {
					if(b->getId(0)) {
						gameState.setGameState(STATE::STATE_MENU_SELECT);
						menuRenderer->setup(STATE::STATE_MENU_SELECT);
					}
					if(b->getId(1)) {
						gameState.setGameState(STATE::STATE_MENU_SETTINGS);
						menuRenderer->setup(STATE::STATE_MENU_SETTINGS);
					}
					if(b->getId(2)) {
						gameState.setGameState(STATE::STATE_MENU_HELP);
						menuRenderer->setup(STATE::STATE_MENU_HELP);
					}
					if(b->getId(3)) {
						exit(EXIT_SUCCESS);
					}
					if(b->getId(4)) {
						gameState.setGameState(STATE::STATE_MENU_MAIN);
						menuRenderer->setup(STATE::STATE_MENU_MAIN);
					}
					if(b->getId(5)) {
						gameState.setGameState(STATE::STATE_GAME_INGAME);
						menuRenderer->setup(STATE::STATE_GAME_INGAME);
					}
				}
			}

			break;

		case sf::Event::MouseMoved:
			for(Gui::Button* b : menuRenderer->getButtons()) {
				if(mouseOver((float_t) e->mouseMove.x, (float_t) e->mouseMove.y, b)) {
					b->hover = true;
				} else {
					b->hover = false;
				}
			}

		default:
			break;
	}
}

void InputHandler::tick() {
	for(Entity* e : entityHandler->entities) {
		if(PlayerEntity* p = dynamic_cast<PlayerEntity*>(e)) {
			if(!p->isControllable())
				return;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				p->setVelY(-4);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				p->setVelY(4);
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				p->setVelY(0);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				p->setVelX(-4);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				p->setVelX(4);
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				p->setVelX(0);
		}
	}
}

bool InputHandler::mouseOver(float_t mx, float_t my, Gui::Button* button) {
	if((mx > button->getX()) && (mx < button->getX() + button->getWidth()))
		if((my > button->getY()) && (my < button->getY() + button->getHeight()))
			return true;

	return false;
}

bool InputHandler::mouseOver(float_t mx, float_t my, float_t x, float_t y, float_t width, float_t height) {
	if((mx > x) && (mx < x + width))
		if((my > y) && (my < y + height))
			return true;

	return false;
}


