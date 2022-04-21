#include "InputHandler.h"

InputHandler::InputHandler(MenuRenderer& menuRenderer, EntityHandler& entityHandler) : menuRenderer(&menuRenderer), entityHandler(&entityHandler), gameState(menuRenderer.gameState) {

}

void InputHandler::update(sf::Event* e) {
	switch(e->type) {
		case sf::Event::MouseButtonPressed:
			for(Gui::Button* b : menuRenderer->getButtons()) {
				if(mouseOver(e->mouseButton.x, e->mouseButton.y, b)) {
					if(b->getId(9) || b->getId(10)) {
						b->down = true;
					}
				}
			}

			if(menuRenderer->isExitUnconfirmed())
				return;

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

			for(Gui::Arrow* a : menuRenderer->getArrows()) {
				if(mouseOver(e->mouseButton.x, e->mouseButton.y, a)) {
					menuRenderer->setGameMode((menuRenderer->getGameMode() == "Infinite") ? "Dual" : "Infinite");
					menuRenderer->resetDrawables();
				}
			}

			break;

		case sf::Event::MouseButtonReleased:
			for(Gui::Button* b : menuRenderer->getButtons()) {
				if(mouseOver(e->mouseButton.x, e->mouseButton.y, b)) {
					if(gameState.getGameState(STATE::STATE_MENU_MAIN)) {
						if(b->getId(9))
							menuRenderer->exitConfirmation();	
						if(b->getId(10))
							exit(EXIT_SUCCESS);
					}
					if(gameState.getGameState(STATE::STATE_GAME_INGAME)) {
						if(b->getId(9))
							menuRenderer->pauseGame();
						if(b->getId(10)) {
							menuRenderer->pauseGame();
							gameState.setGameState(STATE::STATE_MENU_MAIN);
							menuRenderer->setup(STATE::STATE_MENU_MAIN);
						}
					}
				}

				b->down = false;
			}

			if(menuRenderer->isExitUnconfirmed())
					return;

			for(Gui::Button* b : menuRenderer->getButtons()) {
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
						menuRenderer->exitConfirmation();
						//exit(EXIT_SUCCESS);
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
					if(b->getId(8)) {
						gameState.setGameState(STATE::STATE_MENU_SHOP);
						menuRenderer->setup(STATE::STATE_MENU_SHOP);
					}
				}
			}

			for(Gui::Checkbox* c : menuRenderer->getCheckboxes()) {
				if(mouseOver(e->mouseButton.x, e->mouseButton.y, c)) {
					c->click();

					if(c->getId() == 10) {
						if(!c->isChecked())
							for(int i = 0; i < entityHandler->entities.size(); i++)
								if(entityHandler->entities.at(i)->getId() == ID::MenuParticle) {
									entityHandler->entities.erase(entityHandler->entities.begin() + i);
									i--;
								}
						if(c->isChecked())
							entityHandler->addMenuParticles();
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
					if(!menuRenderer->isExitUnconfirmed() || b->getId(9) || b->getId(10))
						b->hover = true;
				} else {
					b->hover = false;
				}
			}

			for(Gui::Slider* s : menuRenderer->getSliders()) {
				if(s->dragging)
					s->setBlockX(e->mouseMove.x - s->mxr);
			}

		case sf::Event::KeyPressed:
			if(e->key.code == sf::Keyboard::Escape) {
				if(gameState.getGameState(STATE::STATE_MENU_MAIN))
					menuRenderer->exitConfirmation();
	
				if(gameState.getGameState(STATE::STATE_MENU_SELECT) || gameState.getGameState(STATE::STATE_MENU_HELP) || gameState.getGameState(STATE::STATE_MENU_SETTINGS) || gameState.getGameState(STATE::STATE_MENU_SHOP)) {
					gameState.setGameState(STATE::STATE_MENU_MAIN);
					menuRenderer->setup(STATE::STATE_MENU_MAIN);
				}

				if(gameState.getGameState(STATE::STATE_GAME_INGAME))
					menuRenderer->pauseGame();
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

			if(p->isPlayerOne()) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					p->setVelY(-5);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					p->setVelY(5);
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					p->setVelY(0);

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					p->setVelX(-5);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					p->setVelX(5);
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					p->setVelX(0);
			}
			if(!p->isPlayerOne()) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					p->setVelY(-5);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					p->setVelY(5);
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					p->setVelY(0);

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					p->setVelX(-5);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					p->setVelX(5);
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					p->setVelX(0);
			}
		}
	}
}

bool InputHandler::mouseOver(double mx, double my, Gui::Button* button) {
	if((mx > button->getX()) && (mx < (button->getX() + button->getWidth())))
		if((my > button->getY()) && (my < (button->getY() + button->getHeight())))
			return true;

	return false;
}

bool InputHandler::mouseOver(double mx, double my, Gui::Checkbox* checkbox) {
	if((mx > checkbox->getX()) && (mx < (checkbox->getX() + checkbox->getWidth())))
		if((my > checkbox->getY() - checkbox->getHeight() / 2 + 5) && (my < (checkbox->getY() - checkbox->getHeight() / 2 + 5 + checkbox->getHeight())))
			return true;

	return false;
}

bool InputHandler::mouseOver(double mx, double my, Gui::Arrow* arrow) {
	if(!arrow->isInverted())
		if((mx > arrow->getX()) && (mx < (arrow->getX() + arrow->getWidth())))
			if((my > arrow->getY()) && (my < (arrow->getY() + arrow->getHeight())))
				return true;

	if(arrow->isInverted())
		if((mx < arrow->getX()) && (mx > (arrow->getX() - arrow->getWidth())))
			if((my > arrow->getY()) && (my < (arrow->getY() + arrow->getHeight())))
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


