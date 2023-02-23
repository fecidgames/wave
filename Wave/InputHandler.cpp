#include "InputHandler.h"
#include "Wave.h"

InputHandler::InputHandler(Wave& wave, MenuRenderer& menuRenderer, EntityHandler& entityHandler) : menuRenderer(&menuRenderer), entityHandler(&entityHandler), gameState(menuRenderer.gameState), wave(wave) {
	
}

void InputHandler::handleButtonPresses(sf::Event* e) {
	// This first loop will only handle buttons that need to be pressable at all times,
	// even when a gui is open or the game is paused.
	for (Gui::Button* button : menuRenderer->getButtons()) {
		if (type(e, sf::Event::MouseButtonPressed)) {
			if (button->getId({ Gui::Button::ID_PAUSE_CONTINUE, Gui::Button::ID_PAUSE_MAINMENU, Gui::Button::ID_QUIT_NO, Gui::Button::ID_QUIT_YES })) {
				if (mouseOver(e->mouseButton, button)) {
					button->press();
					break;
				}
			}
		} else if (type(e, sf::Event::MouseButtonReleased)) {
			if (mouseOver(e->mouseButton, button)) {
				button->notify();

				if (button->getId(Gui::Button::ID_PAUSE_OPTIONS) && menuRenderer->isGamePaused() && menuRenderer->isPauseGuiHidden()) {
					button->release();
					break;
				}

				if (button->getId(Gui::Button::ID_QUIT_NO)) {
					menuRenderer->exitConfirmation();
					button->release();
					return;
				}

				if (button->getId(Gui::Button::ID_QUIT_YES))
					wave.stop();

				if (gameState.getGameState(STATE::STATE_GAME_INGAME) && !menuRenderer->isExitUnconfirmed()) {
					if (button->getId(9)) {
						menuRenderer->pauseGame();
						button->release();
						return;
					}
					if (button->getId(10)) {
						menuRenderer->pauseGame();

						gameState.setGameState(STATE::STATE_MENU_MAIN);
						menuRenderer->setup(STATE::STATE_MENU_MAIN);

						button->release();
						return;
					}
				}
			}
			// Release all potentially pressed buttons, so they don't remain white while the game is paused.
			button->release();
		}
	}

	// Don't allow buttons to be interacted with when the exit gui is open
	if (menuRenderer->isExitUnconfirmed())
		return;

	// Handle all other button interactions
	for (Gui::Button* button : menuRenderer->getButtons())
		if (mouseOver(e->mouseButton, button))
			if (type(e, sf::Event::MouseButtonPressed)) {
				button->press();
			} else if (type(e, sf::Event::MouseButtonReleased)) {
				if (button->getId(Gui::Button::ID_MAIN_GAMEMODES)) {
					gameState.setGameState(STATE::STATE_MENU_SELECT);
					menuRenderer->setup(STATE::STATE_MENU_SELECT);
					return;
				}
				if (button->getId(Gui::Button::ID_MAIN_OPTIONS)) {
					gameState.setGameState(STATE::STATE_MENU_SETTINGS);
					menuRenderer->setup(STATE::STATE_MENU_SETTINGS);
					return;
				}
				if (button->getId(Gui::Button::ID_MAIN_HELP)) {
					gameState.setGameState(STATE::STATE_MENU_HELP);
					menuRenderer->setup(STATE::STATE_MENU_HELP);
					return;
				}
				if (button->getId(Gui::Button::ID_MAIN_QUIT)) {
					menuRenderer->exitConfirmation();
					return;
				}

				if (button->getId(Gui::Button::ID_GLOBAL_BACK)) {
					if (gameState.getLastState(STATE::STATE_GAME_INGAME) && gameState.getGameState(STATE::STATE_MENU_SETTINGS)) {
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
				if (button->getId(Gui::Button::ID_SELECT_PLAY)) {
					gameState.setGameState(STATE::STATE_GAME_INGAME);
					menuRenderer->setup(STATE::STATE_GAME_INGAME);
					menuRenderer->getHud().startTime();
					return;
				}
				if (button->getId(Gui::Button::ID_MAIN_SHOP)) {
					gameState.setGameState(STATE::STATE_MENU_SHOP);
					menuRenderer->setup(STATE::STATE_MENU_SHOP);
					return;
				}
				if (button->getId(Gui::Button::ID_DEBUG_KILLALL)) {
					if (gameState.getGameState(STATE::STATE_GAME_INGAME) && !menuRenderer->isGamePaused()) {
						for (int i = 0; i < entityHandler->entities.size(); i++) {
							if (entityHandler->entities.at(i)->getId() == ID::Player) {
								entityHandler->die((PlayerEntity*)entityHandler->entities.at(i));
							}
						}
					}

					return;
				}
				if (button->getId(99)) {
					if (!gameState.getGameState(STATE::STATE_MENU_SETTINGS)) {
						gameState.setGameState(STATE::STATE_MENU_SETTINGS);

						if (wave.isMenuParticlesEnabled())
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

void InputHandler::handleSliderPresses(sf::Event* e) {
	// Don't allow sliders to be interacted with when the exit gui is open
	if (menuRenderer->isExitUnconfirmed())
		return;

	// Handle slider interactions
	for (Gui::Slider* slider : menuRenderer->getSliders()) {
		if (type(e, sf::Event::MouseButtonPressed)) {
			if (mouseOverBlock(e->mouseButton, slider)) {
				slider->setMXR(e->mouseButton.x - slider->getBlockX());
				slider->drag();
			}

			if (mouseOver(e->mouseButton, slider)) {
				slider->setMXR(slider->getBlockWidth() / 2);
				slider->setBlockX(e->mouseButton.x - slider->getMXR());
				slider->drag();
			}
		} else if (type(e, sf::Event::MouseButtonReleased)) {
			for (Gui::Slider* slider : menuRenderer->getSliders()) {
				if (slider->isDragging()) {
					if (slider->getId(6)) {
						double d = ((double)slider->getBlockX() - (double)slider->getX()) / (double)slider->getLength() * 100.0;
						wave.setVolume(wave.nearest10(d));

						std::cout << "Set volume: " << wave.nearest10(d) << ".\n";
					}
				}

				slider->release();
			}
		}
	}
}

void InputHandler::handleArrowPresses(sf::Event* e) {
	// Don't allow arrows to be interacted with when the exit gui is open
	if (menuRenderer->isExitUnconfirmed())
		return;
	if (type(e, sf::Event::MouseButtonReleased)) {
		for (Gui::Arrow* arrow : menuRenderer->getArrows()) {
			if (mouseOver(e->mouseButton, arrow)) {
				if (arrow->getId(1)) {
					menuRenderer->setGameMode((menuRenderer->getGameMode() == "Infinite") ? "Dual" : "Infinite");
					menuRenderer->resetDrawables();
				}

				if (arrow->getId(2)) {
					gameState.setHelpScreen(gameState.nextHelpScreen());
					menuRenderer->resetDrawables();
				}
				if (arrow->getId(3)) {
					gameState.setHelpScreen(gameState.previousHelpScreen());
					menuRenderer->resetDrawables();
				}
			}
		}
	}
}

void InputHandler::handleCheckboxPresses(sf::Event* e) {
	if (menuRenderer->isExitUnconfirmed())
		return;

	if (type(e, sf::Event::MouseButtonReleased)) {
		for (Gui::Checkbox* checkbox : menuRenderer->getCheckboxes()) {
			if (mouseOver(e->mouseButton, checkbox)) {
				checkbox->click();

				// These settings are handled in Wave.cpp
				if (checkbox->getId(8))
					wave.setVSyncEnabled(checkbox->isChecked());
				if (checkbox->getId(9))
					wave.setFullscreenEnabled(checkbox->isChecked());

				if (checkbox->getId(10)) {
					if (checkbox->isChecked()) {
						wave.setMenuParticlesEnabled(true);
						entityHandler->addMenuParticles();
					}
					if (!checkbox->isChecked()) {
						wave.setMenuParticlesEnabled(false);
						entityHandler->removeMenuParticles();
					}
				}

				if (checkbox->getId(11))
					wave.setDebugMenuEnabled(checkbox->isChecked());
				if (checkbox->getId(12))
					wave.setSoundEnabled(checkbox->isChecked());
			}
		}
	}
}

void InputHandler::update(sf::Event* e) {
	handleButtonPresses(e);
	handleSliderPresses(e);
	handleArrowPresses(e);
	handleCheckboxPresses(e);

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
					double d = ((double) slider->getBlockX() - (double) slider->getX()) / (double) slider->getLength() * 100.0;
					wave.setVolume(wave.nearest10(d));
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
	for (Entity* e : entityHandler->entities) {
		if (PlayerEntity* p = dynamic_cast<PlayerEntity*>(e)) {
			if (!p->isControllable())
				return;

			if (p->isDead()) {
				p->setVelX(0);
				p->setVelY(0);
				return;
			}

			sf::Vector2f movement(0.f, 0.f);

			if (p->isPlayerOne()) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					movement.y -= 1.f;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					movement.y += 1.f;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					movement.x -= 1.f;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					movement.x += 1.f;
			} else {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					movement.y -= 1.f;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					movement.y += 1.f;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					movement.x -= 1.f;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					movement.x += 1.f;
			}

			// Normalize the movement vector if necessary
			float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
			if (length > 1.f) {
				movement /= length;
			}

			// Limit the movement speed to 5 pixels per tick
			movement *= 5.f;

			p->setVelX(movement.x);
			p->setVelY(movement.y);
		}
	}
}

// MouseOver method base for MouseButtonEvent
bool InputHandler::mo(sf::Event::MouseButtonEvent mb, int32_t x, int32_t y, int32_t width, int32_t height) {
	if((mb.x > x) && (mb.x < (x + width)))
		if((mb.y > y) && (mb.y < (y + height)))
			return true;

	return false;
}

// MouseOver method base for MouseMoveEvent
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

bool InputHandler::type(sf::Event* e, sf::Event::EventType type) {
	return e->type == type;
}
