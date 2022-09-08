#include "InputHandler.h"
#include "Wave.h"

InputHandler::InputHandler(Wave& wave, MenuRenderer& menuRenderer, EntityHandler& entityHandler) : menuRenderer(&menuRenderer), entityHandler(&entityHandler), gameState(menuRenderer.gameState), wave(wave) {
	
}

void InputHandler::update(sf::Event* e) {
	if(type(e, sf::Event::MouseButtonPressed)) {
		for(Gui::Button* button : menuRenderer->getButtons()) {
			if(mouseOver(e->mouseButton, button)) {

				//These are the buttons that should still be pressable, even when the rest is paused
				if(button->getId(9) || button->getId(10) || button->getId(90) || button->getId(91)) {
					button->press();
					break;
				}
			}
		}

		//If there is an exit confirm gui, don't allow other buttons to be pressed
		if(menuRenderer->isExitUnconfirmed())
			return;

		/*
		* When there is no game-pausing gui open, handle all other button presses
		*/

		for(Gui::Button* button : menuRenderer->getButtons())
			if(mouseOver(e->mouseButton, button))
				button->press();

		for(Gui::Slider* slider : menuRenderer->getSliders()) {
			if(mouseOverBlock(e->mouseButton, slider)) {
				slider->setMXR(e->mouseButton.x - slider->getBlockX());
				slider->drag();
			}

			if(mouseOver(e->mouseButton, slider)) {
				slider->setMXR(slider->getBlockWidth() / 2);
				slider->setBlockX(e->mouseButton.x - slider->getMXR());
				slider->drag();
			}
		}

		for(Gui::Arrow* arrow : menuRenderer->getArrows()) {
			if(mouseOver(e->mouseButton, arrow)) {
				menuRenderer->setGameMode((menuRenderer->getGameMode() == "Infinite") ? "Dual" : "Infinite");
				menuRenderer->resetDrawables();
			}
		}
	}

	if(type(e, sf::Event::MouseButtonReleased)) {
		//We'll look through the unpausable buttons first
		for(Gui::Button* button : menuRenderer->getButtons()) {
			if(mouseOver(e->mouseButton, button)) {
				button->notify();

				if(button->getId(99) && menuRenderer->isGamePaused() && menuRenderer->isPauseGuiHidden()) {
					button->release();
					break;
				}

				if(button->getId(90)) {
					menuRenderer->exitConfirmation();
					button->release();
					return;
				}
				if(button->getId(91))
					wave.stop();

				if(gameState.getGameState(STATE::STATE_GAME_INGAME) && !menuRenderer->isExitUnconfirmed()) {
					if(button->getId(9)) {
						menuRenderer->pauseGame();
						button->release();
						return;
					}
					if(button->getId(10)) {
						menuRenderer->pauseGame();

						gameState.setGameState(STATE::STATE_MENU_MAIN);
						menuRenderer->setup(STATE::STATE_MENU_MAIN);

						button->release();
						return;
					}
				}
			}

			button->release();
		}

		//If there is an exit confirm gui, don't allow other buttons to perform their actions
		if(menuRenderer->isExitUnconfirmed())
			return;

		/*
		* When there is no game-pausing gui open, handle all other button releases & actions
		*/

		//Button actions per id
		for(Gui::Button* button : menuRenderer->getButtons()) {
			if(mouseOver(e->mouseButton, button)) {
				if(button->getId(0)) {
					gameState.setGameState(STATE::STATE_MENU_SELECT);
					menuRenderer->setup(STATE::STATE_MENU_SELECT);
					return;
				}
				if(button->getId(1)) {
					gameState.setGameState(STATE::STATE_MENU_SETTINGS);
					menuRenderer->setup(STATE::STATE_MENU_SETTINGS);
					return;
				}
				if(button->getId(2)) {
					gameState.setGameState(STATE::STATE_MENU_HELP);
					menuRenderer->setup(STATE::STATE_MENU_HELP);
					return;
				}
				if(button->getId(3)) {
					menuRenderer->exitConfirmation();
					return;
				}

				if(button->getId(4)) {
					if(gameState.getLastState(STATE::STATE_GAME_INGAME) && gameState.getGameState(STATE::STATE_MENU_SETTINGS)) {
						gameState.revertGameState();

						entityHandler->removeMenuParticles();
						entityHandler->hideHostileEntities();
						entityHandler->hidePlayer();

						menuRenderer->hidePauseGUI();
						menuRenderer->setupInGame(STATE::STATE_GAME_INGAME);
						return;
					}

					gameState.setGameState(STATE::STATE_MENU_MAIN);
					menuRenderer->setup(STATE::STATE_MENU_MAIN);
					return;
				}
				if(button->getId(5)) {
					gameState.setGameState(STATE::STATE_GAME_INGAME);
					menuRenderer->setup(STATE::STATE_GAME_INGAME);
					menuRenderer->getHud().startTime();
					return;
				}
				if(button->getId(8)) {
					gameState.setGameState(STATE::STATE_MENU_SHOP);
					menuRenderer->setup(STATE::STATE_MENU_SHOP);
					return;
				}
				if(button->getId(11)) {
					gameState.setGameState(STATE::STATE_MENU_SETTINGS);
					menuRenderer->setup(STATE::STATE_MENU_SETTINGS);
					return;
				}
				if(button->getId(40)) {
					if (gameState.getGameState(STATE::STATE_GAME_INGAME) && !menuRenderer->isGamePaused()) {
						for (int i = 0; i < entityHandler->entities.size(); i++) {
							if (entityHandler->entities.at(i)->getId() == ID::Player) {
								if (gameState.getGameMode(MODE::MODE_INFINITE)) {
									entityHandler->die((PlayerEntity*) entityHandler->entities.at(i));
									return;
								}
								else {
									if (gameState.getGameMode(MODE::MODE_DUAL)) {
										PlayerEntity* pe = (PlayerEntity*)entityHandler->entities.at(i);
										//handle player death for 2 players (currently bugged so fix~)
									}
								}
							}
						}
					}

					return;
				}
				if(button->getId(99)) {
					if(!gameState.getGameState(STATE::STATE_MENU_SETTINGS)) {
						gameState.setGameState(STATE::STATE_MENU_SETTINGS);

						if(wave.isMenuParticlesEnabled())
							entityHandler->addMenuParticles();

						entityHandler->hideHostileEntities();
						entityHandler->hidePlayer();

						menuRenderer->hidePauseGUI();
						menuRenderer->setupInGame(STATE::STATE_MENU_SETTINGS);

						return;
					}
				}
			}
		}

		//Checkbox actions per id
		for(Gui::Checkbox* checkbox : menuRenderer->getCheckboxes()) {
			if(mouseOver(e->mouseButton, checkbox)) {
				checkbox->click();

				if(checkbox->getId(8)) { //vSync is handled in the wave class ;)
					if(checkbox->isChecked()) 
						wave.setVSyncEnabled(true);
					if(!checkbox->isChecked())
						wave.setVSyncEnabled(false);
				}
				if(checkbox->getId(9)) {
					if(checkbox->isChecked())
						wave.setFullscreenEnabled(true);
					if(!checkbox->isChecked())
						wave.setFullscreenEnabled(false);
				}
				if(checkbox->getId(10)) {
					if(checkbox->isChecked()) {
						wave.setMenuParticlesEnabled(true);
						entityHandler->addMenuParticles();
					} 
					if(!checkbox->isChecked()){
						wave.setMenuParticlesEnabled(false);
						entityHandler->removeMenuParticles();
					}
				}
				if(checkbox->getId(11)) {
					if(checkbox->isChecked()) {
						wave.setDebugMenuEnabled(true);
					}
					if(!checkbox->isChecked()) {
						wave.setDebugMenuEnabled(false);
					}
				}
			}
		}

		//Slider release & setting adjustment per id
		for(Gui::Slider* slider : menuRenderer->getSliders()) {
			if(slider->isDragging()) {
				if(slider->getId(6)) {
					double d = (slider->getBlockX() - slider->getX()) / (double) slider->getLength() * 100.0;
					int32_t e = wave.nearest10(d);
					wave.setVolume(e);
					std::cout << "Set volume: " << e << ".\n";
				}
			}

			slider->release();
		}
	}

	if(type(e, sf::Event::MouseMoved)) {
		//Handle button hover
		for(Gui::Button* button : menuRenderer->getButtons()) {
			if(mouseOver(e->mouseMove, button)) {
				//If there is no exit gui, handle all hovers, if there is, just for button 90 and 91
				if(!menuRenderer->isExitUnconfirmed() || button->getId(90) || button->getId(91))
					button->hover();
			} else {
				button->unHover();
			}
		}

		for(Gui::Slider* slider : menuRenderer->getSliders())
			if(slider->isDragging()) {
				slider->setBlockX(e->mouseMove.x - slider->getMXR());
				if(slider->getId(6)) {
					double d = (slider->getBlockX() - slider->getX()) / (double) slider->getLength() * 100.0;
					int32_t e = wave.nearest10(d);
					wave.setVolume(e);
					std::cout << "Set volume: " << e << ".\n";
				}
			}
	}

	if(type(e, sf::Event::KeyPressed)) {
		if(e->key.code == sf::Keyboard::Escape) {
			if(gameState.getGameState(STATE::STATE_MENU_MAIN))
				menuRenderer->exitConfirmation();

			if(gameState.getGameState(STATE::STATE_MENU_SETTINGS)) {
				if(gameState.getLastState(STATE::STATE_MENU_MAIN)) {
					gameState.revertGameState();
					menuRenderer->setup(gameState.getGameState());
				} else {
					gameState.setGameState(STATE::STATE_GAME_INGAME);

					entityHandler->removeMenuParticles();
					entityHandler->hideHostileEntities();
					entityHandler->hidePlayer();

					menuRenderer->hidePauseGUI();
					menuRenderer->setupInGame(STATE::STATE_GAME_INGAME);
				}

				return;
			}
	
			if(gameState.getGameState(STATE::STATE_MENU_SELECT) || gameState.getGameState(STATE::STATE_MENU_GAMEOVER) || gameState.getGameState(STATE::STATE_MENU_HELP) || gameState.getGameState(STATE::STATE_MENU_SETTINGS) || gameState.getGameState(STATE::STATE_MENU_SHOP)) {
				gameState.setGameState(STATE::STATE_MENU_MAIN);
				menuRenderer->setup(STATE::STATE_MENU_MAIN);
			}

			if(gameState.getGameState(STATE::STATE_GAME_INGAME) && !menuRenderer->isExitUnconfirmed())
				menuRenderer->pauseGame();
		}

		if(e->key.code == sf::Keyboard::F4) {
			wave.setDebugMenuEnabled(!wave.isDebugMenuEnabled());
			if(gameState.getGameState(STATE::STATE_MENU_SETTINGS))
				menuRenderer->setup(STATE::STATE_MENU_SETTINGS);
		}
	}
}

void InputHandler::tick() {
	for(Entity* e : entityHandler->entities) {
		if(PlayerEntity* p = dynamic_cast<PlayerEntity*>(e)) {
			if(!p->isControllable())
				return;

			if(p->isDead()) {
				p->setVelX(0);
				p->setVelY(0);
				return;
			}

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

bool InputHandler::mo(sf::Event::MouseButtonEvent mb, int32_t x, int32_t y, int32_t width, int32_t height) {
	if((mb.x > x) && (mb.x < (x + width)))
		if((mb.y > y) && (mb.y < (y + height)))
			return true;

	return false;
}

bool InputHandler::mo(sf::Event::MouseMoveEvent mb, int32_t x, int32_t y, int32_t width, int32_t height) {
	if((mb.x > x) && (mb.x < (x + width)))
		if((mb.y > y) && (mb.y < (y + height)))
			return true;

	return false;
}

bool InputHandler::mouseOver(sf::Event::MouseButtonEvent mb, Gui::Button* button) {
	return mo(mb, button->getX(), button->getY(), button->getWidth(), button->getHeight());
}

bool InputHandler::mouseOver(sf::Event::MouseMoveEvent mb, Gui::Button* button) {
	return mo(mb, button->getX(), button->getY(), button->getWidth(), button->getHeight());
}

bool InputHandler::mouseOver(sf::Event::MouseButtonEvent mb, Gui::Checkbox* checkbox) {
	return mo(mb, checkbox->getX(), checkbox->getY(), checkbox->getWidth(), checkbox->getHeight());
}

bool InputHandler::mouseOver(sf::Event::MouseButtonEvent mb, Gui::Arrow* arrow) {
	if(!arrow->isInverted())
		if((mb.x > arrow->getX()) && (mb.x < (arrow->getX() + arrow->getWidth())))
			if((mb.y > arrow->getY()) && (mb.y < (arrow->getY() + arrow->getHeight())))
				return true;

	if(arrow->isInverted())
		if((mb.x < arrow->getX()) && (mb.x > (arrow->getX() - arrow->getWidth())))
			if((mb.y > arrow->getY()) && (mb.y < (arrow->getY() + arrow->getHeight())))
				return true;

	return false;
}

bool InputHandler::mouseOver(sf::Event::MouseButtonEvent mb, Gui::Slider* slider) {
	if((mb.x > slider->getX()) && (mb.x < (slider->getX() + slider->getLength())))
		if((mb.y > slider->getY() - slider->getBlockHeight() / 2) && (mb.y < (slider->getY() + slider->getBlockHeight() / 2)))
			return true;

	return false;
}

bool InputHandler::mouseOverBlock(sf::Event::MouseButtonEvent mb, Gui::Slider* slider) {
	if((mb.x > slider->getBlockX()) && (mb.x < (slider->getBlockX() + slider->getBlockWidth())))
		if((mb.y > slider->getY() - slider->getBlockHeight() / 2) && (mb.y < (slider->getY() + slider->getBlockHeight() / 2)))
			return true;

	return false;
}

bool InputHandler::mouseOver(double mx, double my, double x, double y, double width, double height) {
	if((mx > x) && (mx < x + width))
		if((my > y) && (my < y + height))
			return true;

	return false;
}

bool InputHandler::type(sf::Event* e, sf::Event::EventType type) {
	return e->type == type;
}
