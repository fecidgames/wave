#include "InputHandler.h"

InputHandler::InputHandler(MenuRenderer& menuRenderer, EntityHandler& entityHandler) : menuRenderer(&menuRenderer), entityHandler(&entityHandler), gameState(menuRenderer.gameState) {

}

void InputHandler::update(sf::Event* e) {
	switch(e->type) {
		case sf::Event::MouseButtonPressed:
			for(Gui::Button* b : menuRenderer->getButtons()) {
				if(mouseOver(e->mouseButton.x, e->mouseButton.y, b)) {
					b->down = true;
				}
			}

			for(Gui::Slider* s : menuRenderer->getSliders()) {
				if(mouseOverBlock(e->mouseButton.x, e->mouseButton.y, s)) {
					s->mxr = e->mouseButton.x - s->getBlockX();
					s->dragging = true;
				}

				if(mouseOver(e->mouseButton.x, e->mouseButton.y, s)) {
					s->mxr = s->getBlockWidth() / 2;
					s->setBlockX(e->mouseButton.x - s->mxr);
					s->dragging = true;
				}
			}

			break;

		case sf::Event::MouseButtonReleased:
			for(Gui::Button* b : menuRenderer->getButtons()) {
				b->down = false;

				if(mouseOver(e->mouseButton.x, e->mouseButton.y, b)) {
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
						menuRenderer->getHud().startTime();
					}
				}
			}

			for(Gui::Slider* s : menuRenderer->getSliders()) {
				s->dragging = false;
			}

			break;

		case sf::Event::MouseMoved:
			for(Gui::Button* b : menuRenderer->getButtons()) {
				if(mouseOver(e->mouseMove.x, e->mouseMove.y, b)) {
					b->hover = true;
				} else {
					b->hover = false;
				}
			}

			for(Gui::Slider* s : menuRenderer->getSliders()) {
				if(s->dragging)
					s->setBlockX(e->mouseMove.x - s->mxr);
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

bool InputHandler::mouseOver(double mx, double my, Gui::Button* button) {
	if((mx > button->getX()) && (mx < (button->getX() + button->getWidth())))
		if((my > button->getY()) && (my < (button->getY() + button->getHeight())))
			return true;

	return false;
}

bool InputHandler::mouseOver(double mx, double my, Gui::Slider* slider) {
	if((mx > slider->getX()) && (mx < (slider->getX() + slider->getLength())))
		if((my > slider->getY() - slider->getBlockHeight() / 2) && (my < (slider->getY() + slider->getBlockHeight() / 2)))
			return true;

	return false;
}

bool InputHandler::mouseOverBlock(double mx, double my, Gui::Slider* slider) {
	if((mx > slider->getBlockX()) && (mx < (slider->getBlockX() + slider->getBlockWidth())))
		if((my > slider->getY() - slider->getBlockHeight() / 2) && (my < (slider->getY() + slider->getBlockHeight() / 2)))
			return true;

	return false;
}

bool InputHandler::mouseOver(double mx, double my, double x, double y, double width, double height) {
	if((mx > x) && (mx < x + width))
		if((my > y) && (my < y + height))
			return true;

	return false;
}


