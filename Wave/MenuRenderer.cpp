#include "MenuRenderer.h"
#include "Wave.h"

MenuRenderer::MenuRenderer(Wave& wave, EntityHandler& e, HUD& hud, GameState& state) : e(e), hud(hud), gameState(state), wave(wave) {
	
}

MenuRenderer::~MenuRenderer() {
	for(Gui::Button* b : buttons)
		delete b;
	
	for(Gui::Checkbox* c : checkboxes)
		delete c;

	for(Gui::Slider* s : sliders)
		delete s;

	for(Gui::Arrow* a : arrows)
		delete a;
}

void MenuRenderer::setup(STATE gameState) {
	if(!menuFont.loadFromFile("fonts/mainFont.ttf"))
		throw "[mainFont.ttf] could not be loaded";

	time = 0; //Resets time for player AI

	clearLists();

	setupDrawables(gameState);
	setupButtons(gameState);
	setupEntities(gameState);
}

void MenuRenderer::resetDrawables() {
	clearLists();

	setupDrawables(gameState.getGameState());
	setupButtons(gameState.getGameState());
}

void MenuRenderer::clearLists() {
	rects.clear();
	texts.clear();

	buttons.clear();
	sliders.clear();
	checkboxes.clear();
	arrows.clear();
}

void MenuRenderer::setupDrawables(STATE gameState) {
	if(gameState == STATE::STATE_MENU_MAIN) {
		sf::Text title("Wave!", menuFont, 50);
		title.setPosition(wave.getWindow()->getSize().x / 2 - title.getGlobalBounds().width / 2, 40);

		sf::Text version("v1.1", menuFont, (uint32_t) (15 * wave.getScale()));
		version.setPosition(5, wave.getWindow()->getSize().y - 5 - version.getGlobalBounds().height);

		texts.insert(texts.begin(), title);
		texts.insert(texts.begin(), version);
	}

	if(gameState == STATE::STATE_MENU_SELECT) {
		sf::RectangleShape r1;
		r1.setPosition(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), 16 * wave.getScale());
		r1.setSize(sf::Vector2f((wave.getWindow()->getSize().x / 2 - (32 * wave.getScale())), (wave.getWindow()->getSize().y - (32 * wave.getScale()))));
		r1.setFillColor(sf::Color::Black);
		r1.setOutlineColor(sf::Color::White);
		r1.setOutlineThickness(1.0f);

		double fontMultiplier = (wave.getScale() > 1.6) ? 1.6 : wave.getScale();

		sf::Text select("Select gamemode", menuFont, 35 * fontMultiplier);
		select.setPosition(wave.getWindow()->getSize().x / 4 - select.getGlobalBounds().width / 2, 10);

		sf::Text gamemode("Infinite..", menuFont, 21 * fontMultiplier);
		gamemode.setPosition(wave.getWindow()->getSize().x / 4 - gamemode.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 2 - gamemode.getGlobalBounds().height / 2);

		arrows.insert(arrows.begin(), new Gui::Arrow(gamemode.getPosition().x - 10, gamemode.getPosition().y, 30, gamemode.getGlobalBounds().height + 6, true, 0));
		arrows.insert(arrows.begin(), new Gui::Arrow(gamemode.getPosition().x + 10 + gamemode.getGlobalBounds().width, gamemode.getPosition().y, 30, gamemode.getGlobalBounds().height + 6, false, 0));

		gamemode.setString(gameMode);
		gamemode.setPosition(wave.getWindow()->getSize().x / 4 - gamemode.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 2 - gamemode.getGlobalBounds().height / 2);

		sf::Text desc1(descriptionr1, menuFont, 21 * fontMultiplier);
		desc1.setPosition(wave.getWindow()->getSize().x / 4 - desc1.getGlobalBounds().width / 2, (int32_t) (wave.getWindow()->getSize().y / 2 - desc1.getGlobalBounds().height / 2 - 100));

		sf::Text desc2(descriptionr2, menuFont, 21 * fontMultiplier);
		desc2.setPosition(wave.getWindow()->getSize().x / 4 - desc2.getGlobalBounds().width / 2, (int32_t) (wave.getWindow()->getSize().y / 2 - desc2.getGlobalBounds().height / 2 - 100 + desc1.getGlobalBounds().height + 5));		

		texts.insert(texts.begin(), select);
		texts.insert(texts.begin(), gamemode);
		texts.insert(texts.begin(), desc1);
		texts.insert(texts.begin(), desc2);

		rects.insert(rects.begin(), r1);
	}

	if(gameState == STATE::STATE_GAME_INGAME) {
		sf::Text pause("[ESC] Pause", menuFont, 22);
		pause.setPosition(8, Window::HEIGHT - 8 - pause.getGlobalBounds().height);
		pause.setOutlineColor(sf::Color::Black);
		pause.setOutlineThickness(2.0f);

		sf::Text shop("[TAB] Shop", menuFont, 22);
		shop.setPosition(Window::WIDTH - shop.getGlobalBounds().width - 8, Window::HEIGHT - 8 - shop.getGlobalBounds().height);
		shop.setOutlineColor(sf::Color::Black);
		shop.setOutlineThickness(2.0f);

		texts.insert(texts.begin(), pause);
		texts.insert(texts.begin(), shop);
	}

	if(gameState == STATE::STATE_MENU_SETTINGS) {
		sf::Text title("Options", menuFont, 50);
		title.setPosition(wave.getWindow()->getSize().x / 2 - title.getGlobalBounds().width / 2, 40);

		double xOffset = 50.0 * wave.getScale();

		sf::Text volume("Volume", menuFont, 30);
		volume.setPosition(xOffset, 113);

		sf::Text hudScale("HUD size", menuFont, 30);
		hudScale.setPosition(xOffset, 170);

		sf::Text vSync("vSync", menuFont, 30);
		vSync.setPosition(xOffset, 170 + 57);

		sf::Text fullscreen("Fullscreen", menuFont, 30);
		fullscreen.setPosition(xOffset, 170 + 2 * 57);

		sf::Text mp("Menu Particles", menuFont, 30);
		mp.setPosition(xOffset, 170 + 3 * 57);

		sf::Text dm("Debug menu", menuFont, 30);
		dm.setPosition(xOffset, 170 + 4 * 57);

		texts.insert(texts.begin(), title);
		texts.insert(texts.begin(), volume);
		texts.insert(texts.begin(), hudScale);
		texts.insert(texts.begin(), vSync);
		texts.insert(texts.begin(), fullscreen);
		texts.insert(texts.begin(), mp);
		texts.insert(texts.begin(), dm);


		double cbOffset = mp.getPosition().x + (double) mp.getGlobalBounds().width + (20.0 * wave.getScale());

		checkboxes.insert(checkboxes.begin(), new Gui::Checkbox(cbOffset, 187 + 57, 2, wave.isVSyncEnabled(), 8));
		checkboxes.insert(checkboxes.begin(), new Gui::Checkbox(cbOffset, 187 + 2 * 57, 2, wave.isFullscreenEnabled(), 9));
		checkboxes.insert(checkboxes.begin(), new Gui::Checkbox(cbOffset, 187 + 3 * 57, 2, wave.isMenuParticlesEnabled(), 10));	//Menuparticles checkbox
		checkboxes.insert(checkboxes.begin(), new Gui::Checkbox(cbOffset, 187 + 4 * 57, 2, wave.isDebugMenuEnabled(), 11));		//Debugmenu checkbox

		double blockSizeMultiplier = (wave.getScale() > 1.7) ? 1.7 : wave.getScale();

		sliders.insert(sliders.begin(), new Gui::Slider(cbOffset, 130, wave.getWindow()->getSize().x - cbOffset - (16.0 * wave.getScale()), 16 * blockSizeMultiplier, 32 * blockSizeMultiplier, 6));
		sliders.insert(sliders.begin(), new Gui::Slider(cbOffset, 187, wave.getWindow()->getSize().x - cbOffset - (16.0 * wave.getScale()), 16 * blockSizeMultiplier, 32 * blockSizeMultiplier, 7));
	}

	if(gameState == STATE::STATE_MENU_GAMEOVER) {
		sf::Text title("Game over", menuFont, 50);
		title.setPosition(Window::WIDTH / 2 - title.getGlobalBounds().width / 2, 40);

		sf::Text winner("Winner: " + winningPlayer, menuFont, 30);
		winner.setPosition(8, title.getPosition().y + title.getGlobalBounds().height + 8 + 16);

		sf::Text playTimeInf("Time: " + pTime, menuFont, 30);
		sf::Text playTimeDua("Time: " + pTime, menuFont, 30);
		playTimeInf.setPosition(Window::WIDTH / 2 - playTimeDua.getGlobalBounds().width / 2, title.getPosition().y + title.getGlobalBounds().height + 8 + 16);
		playTimeDua.setPosition(Window::WIDTH - playTimeInf.getGlobalBounds().width - 8, title.getPosition().y + title.getGlobalBounds().height + 8 + 16);

		texts.insert(texts.begin(), title);

		if(!wave.getGameState().getGameMode(MODE::MODE_INFINITE)) {
			texts.insert(texts.begin(), playTimeDua);
			texts.insert(texts.begin(), winner);
		} else {
			texts.insert(texts.begin(), playTimeInf);
		}
	}
}

void MenuRenderer::setupEntities(STATE gameState) {
	for(int i = 0; i < e.entities.size(); ++i) {
		if(e.entities.at(i)->renderOverGui() && e.entities.at(i)->getId() == ID::MenuParticle || e.entities.at(i)->getId() == ID::Player) {
			e.entities.erase(e.entities.begin() + i);
			i--;
		}
	}

	if(gameState != STATE::STATE_GAME_INGAME) {
		for(int i = 0; i < e.entities.size(); ++i) {
			if(e.entities.at(i)->getId() == ID::BasicEnemy || e.entities.at(i)->getId() == ID::FastEnemy || e.entities.at(i)->getId() == ID::SmartEnemy) {
				e.entities.erase(e.entities.begin() + i);
				i--;
			}
		}
	}

	if(gameState == STATE::STATE_MENU_MAIN) {
		for(int i = 0; i < e.entities.size(); ++i) {
			if(e.entities.at(i)->getId() == ID::MenuParticle)
				return;
		}

		if(wave.isMenuParticlesEnabled())
			e.addMenuParticles();
	}

	if(gameState == STATE::STATE_MENU_SELECT) {
		e.add(new MenuParticleEntity(
			wave.getWindow()->getSize().x / 2 + 50, 50, 
			ID::MenuParticle, 16, 

			sf::Vector2f(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), wave.getWindow()->getSize().x - (16 * wave.getScale())), 
			sf::Vector2f(16 * wave.getScale(), wave.getWindow()->getSize().y - (16 * wave.getScale())), 
			
			e, true, wave.getScale())
		);
		
		e.add(new MenuParticleEntity(
			wave.getWindow()->getSize().x / 3 + wave.getWindow()->getSize().x / 2 - 62, 
			wave.getWindow()->getSize().y / 2, 
			ID::MenuParticle, 16, 
			
			sf::Vector2f(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), wave.getWindow()->getSize().x - (16 * wave.getScale())), 
			sf::Vector2f(16 * wave.getScale(), wave.getWindow()->getSize().y - (16 * wave.getScale())), 
			
			e, true, wave.getScale())
		);
		
		e.add(new MenuParticleEntity(
			wave.getWindow()->getSize().x - wave.getWindow()->getSize().x / 3, 
			wave.getWindow()->getSize().y - wave.getWindow()->getSize().y / 4, 
			ID::MenuParticle, 16, 
			
			sf::Vector2f(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), wave.getWindow()->getSize().x - (16 * wave.getScale())), 
			sf::Vector2f(16 * wave.getScale(), wave.getWindow()->getSize().y - (16 * wave.getScale())), 
			
			e, true, wave.getScale())
		);
		
		e.add(new MenuParticleEntity(
			wave.getWindow()->getSize().x - wave.getWindow()->getSize().x / 4, 
			wave.getWindow()->getSize().y / 4, 
			ID::MenuParticle, 16, 
			
			sf::Vector2f(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), wave.getWindow()->getSize().x - (16 * wave.getScale())), 
			sf::Vector2f(16 * wave.getScale(), wave.getWindow()->getSize().y - (16 * wave.getScale())), 
			
			e, true, wave.getScale())
		);
		
		e.add(new PlayerEntity(
			wave.getWindow()->getSize().x - wave.getWindow()->getSize().x / 4 - 16, 
			wave.getWindow()->getSize().y / 2 - 16, 
			ID::Player, 18, 
			
			sf::Vector2i(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), wave.getWindow()->getSize().x - (16 * wave.getScale())),
			sf::Vector2i(16 * wave.getScale(), wave.getWindow()->getSize().y - (16 * wave.getScale())), 
			
			e, true, false, wave.getScale()));
	}

	if(gameState == STATE::STATE_GAME_INGAME) {
		e.entities.clear();
		if(this->gameState.getGameMode() == MODE::MODE_INFINITE) {
			e.add(new PlayerEntity(Window::WIDTH / 2 - 16, Window::HEIGHT / 2 - 16, ID::Player, 17, sf::Vector2i(0, Window::WIDTH), sf::Vector2i(0, Window::HEIGHT), e, false, true, hud.getMaxHealth(), wave.getScale()));	
		}
		if(this->gameState.getGameMode() == MODE::MODE_DUAL) {
			e.add(new PlayerEntity(Window::WIDTH / 2 - 16, Window::HEIGHT / 2 - 16, ID::Player, 17, sf::Vector2i(0, Window::WIDTH), sf::Vector2i(0, Window::HEIGHT), e, false, true, hud.getMaxHealth(), wave.getScale()));	
			e.add(new PlayerEntity(Window::WIDTH / 2 - 16, Window::HEIGHT / 2 - 16, ID::Player, 17, sf::Vector2i(0, Window::WIDTH), sf::Vector2i(0, Window::HEIGHT), e, false, true, hud.getMaxHealth(), wave.getScale()));	
		}
	}

	if(gameState == STATE::STATE_MENU_GAMEOVER) {
	
	}
}

void MenuRenderer::setupButtons(STATE gameState) {
	//LAST BUTTON ID: 11

	if(gameState == STATE::STATE_MENU_MAIN) {
		buttons.insert(buttons.begin(), new Gui::Button((wave.getWindow()->getSize().x / 2 - 190), 130, 380, 64, "Gamemodes", 0));
		buttons.insert(buttons.begin(), new Gui::Button((wave.getWindow()->getSize().x / 2 - 190), 210, 380, 64, "Options", 1));
		buttons.insert(buttons.begin(), new Gui::Button((wave.getWindow()->getSize().x / 2 - 190 + 396), 130, 64, 64, "?", 2));
		buttons.insert(buttons.begin(), new Gui::Button((wave.getWindow()->getSize().x - (380 / 2) - (16 * wave.getScale())), wave.getWindow()->getSize().y - 64 - (16 * wave.getScale()), (380 / 2), 64, "Quit", 3));
		buttons.insert(buttons.begin(), new Gui::Button((wave.getWindow()->getSize().x / 2 - 190), 290, 380, 64, "Shop", 8));
	}

	if(gameState == STATE::STATE_MENU_SELECT) {
		buttons.insert(buttons.begin(), new Gui::Button(16 * wave.getScale(), wave.getWindow()->getSize().y - 64 - (16 * wave.getScale()), (380 / 2), 64, "Back", 4));
		buttons.insert(buttons.begin(), new Gui::Button(16 * wave.getScale(), wave.getWindow()->getSize().y - 280, (wave.getWindow()->getSize().x / 2) - (32 * wave.getScale()), 64, "Play gamemode", 5));
	}

	if(gameState == STATE::STATE_MENU_SETTINGS) {
		buttons.insert(buttons.begin(), new Gui::Button(16 * wave.getScale(), wave.getWindow()->getSize().y - 64 - (16 * wave.getScale()), (380 / 2), 64, "Back", 4));
	}
	
	if(gameState == STATE::STATE_MENU_GAMEOVER) {
		
	}
}

void MenuRenderer::pauseGame(bool paused) {
	gamePaused = paused;

	if(gamePaused) {
		hud.pauseTime();

		buttons.insert(buttons.begin(), new Gui::Button((Window::WIDTH / 4) / 2 + 8, Window::HEIGHT / 5 + 3 * (Window::HEIGHT / 5) - 64 - 8, (Window::WIDTH - (Window::WIDTH / 4)) / 2 - 16, 64, "Continue", 9));
		buttons.insert(buttons.begin(), new Gui::Button(((Window::WIDTH / 4) / 2) + (Window::WIDTH - (Window::WIDTH / 4)) - ((Window::WIDTH - (Window::WIDTH / 4)) / 2) + 8, Window::HEIGHT / 5 + 3 * (Window::HEIGHT / 5) - 64 - 8, (Window::WIDTH - (Window::WIDTH / 4)) / 2 - 16, 64, "Back to menu", 10));
		buttons.insert(buttons.begin(), new Gui::Button((Window::WIDTH / 4) / 2 + 8, Window::HEIGHT / 5 + 3 * (Window::HEIGHT / 5) - 2 * 64 - 16, (Window::WIDTH - (Window::WIDTH / 4)) - 16, 64, "Settings", 11));
	} else {
		hud.resumeTime();

		for(int i = 0; i < buttons.size(); i++) {
			if(buttons.at(i)->getId(9) || buttons.at(i)->getId(10) || buttons.at(i)->getId(11)) {
				buttons.erase(buttons.begin() + i);
				i--;
			}
		}
	}
}

void MenuRenderer::pauseGame() {
	gamePaused = !gamePaused;

	if(gamePaused) {
		hud.pauseTime();

		buttons.insert(buttons.begin(), new Gui::Button((Window::WIDTH / 4) / 2 + 8, Window::HEIGHT / 5 + 3 * (Window::HEIGHT / 5) - 64 - 8, (Window::WIDTH - (Window::WIDTH / 4)) / 2 - 16, 64, "Continue", 9));
		buttons.insert(buttons.begin(), new Gui::Button(((Window::WIDTH / 4) / 2) + (Window::WIDTH - (Window::WIDTH / 4)) - ((Window::WIDTH - (Window::WIDTH / 4)) / 2) + 8, Window::HEIGHT / 5 + 3 * (Window::HEIGHT / 5) - 64 - 8, (Window::WIDTH - (Window::WIDTH / 4)) / 2 - 16, 64, "Back to menu", 10));
		buttons.insert(buttons.begin(), new Gui::Button((Window::WIDTH / 4) / 2 + 8, Window::HEIGHT / 5 + 3 * (Window::HEIGHT / 5) - 2 * 64 - 16, (Window::WIDTH - (Window::WIDTH / 4)) - 16, 64, "Settings", 11));
	} else {
		hud.resumeTime();

		for(int i = 0; i < buttons.size(); i++) {
			if(buttons.at(i)->getId(9) || buttons.at(i)->getId(10) || buttons.at(i)->getId(11)) {
				buttons.erase(buttons.begin() + i);
				i--;
			}
		}
	}
}

void MenuRenderer::gameEnd() {
	for(int32_t i = 0; i < e.entities.size(); i++) {
		if(e.entities.at(i)->getId() == ID::Player) {
			e.entities.erase(e.entities.begin() + i);
			i--;
		}
	}

	gameState.setGameState(STATE::STATE_MENU_GAMEOVER);
	setup(STATE::STATE_MENU_GAMEOVER);
}

void MenuRenderer::exitConfirmation() {
	exitConfirmationPopup = !exitConfirmationPopup;

	if(exitConfirmationPopup) {
		buttons.insert(buttons.begin(), new Gui::Button(Window::WIDTH / 2 + 8, Window::HEIGHT / 2, ((Window::WIDTH - (Window::WIDTH / 3)) / 2) - 16, 64, "No", 90));
		buttons.insert(buttons.begin(), new Gui::Button((Window::WIDTH / 3) / 2 + 8, Window::HEIGHT / 2, (Window::WIDTH - (Window::WIDTH / 3)) / 2 - 16, 64, "Yes", 100));
	} else {
		for(int i = 0; i < buttons.size(); i++) {
			if(buttons.at(i)->getId(90) || buttons.at(i)->getId(100)) {
				buttons.erase(buttons.begin() + i);
				i--;
			}
		}
	}
}

void MenuRenderer::render(sf::RenderWindow& window, bool onTop) {
	if(!onTop) {
		for(Gui::Button* b : buttons)
			b->render(window);

		for(Gui::Slider* s : sliders)
			s->render(window);

		for(Gui::Checkbox* c : checkboxes)
			c->render(window);

		for(Gui::Arrow* a : arrows)
			a->render(window);


		for(sf::Text t : texts)
			window.draw(t);

		for(sf::RectangleShape r : rects)
			window.draw(r);

		//======================================================//

		if(gameState.getGameState(STATE::STATE_GAME_INGAME))
			hud.render();

		if(gameState.getGameState(STATE::STATE_MENU_SELECT)) {
			for(int i = 0; i < e.entities.size(); i++) {
				if(e.entities.at(i)->getId() == ID::Player) {

					PlayerEntity* p = (PlayerEntity*) e.entities.at(i);
					if(!p->isControllable()) {
						if(time < 1)
							p->setVelX(5);

						time++;
						std::srand(time);
						playerPos(p);
					}
				}
			}
		}

		//==========================================================//

		if(gamePaused) {
			sf::RectangleShape pauseBackground;
			pauseBackground.setFillColor(sf::Color::Black);
			pauseBackground.setOutlineColor(sf::Color::White);
			pauseBackground.setOutlineThickness(2);
			pauseBackground.setPosition(sf::Vector2f((Window::WIDTH / 4) / 2, Window::HEIGHT / 5));
			pauseBackground.setSize(sf::Vector2f(Window::WIDTH - (Window::WIDTH / 4), 3 * (Window::HEIGHT / 5)));

			sf::Text title("Game paused", menuFont, 40);
			title.setPosition(pauseBackground.getPosition().x + pauseBackground.getGlobalBounds().width / 2 - title.getGlobalBounds().width / 2, pauseBackground.getPosition().y + 16);

			window.draw(pauseBackground);
			window.draw(title);

			for(Gui::Button* b : buttons)
				if(b->getId(9) || b->getId(10) || b->getId(11))
					b->render(window);
		}
	}

	if(onTop) {
		if(exitConfirmationPopup) {
			Gui::Button* ye = new Gui::Button((Window::WIDTH / 3) / 2 + 8, Window::HEIGHT / 2, (Window::WIDTH - (Window::WIDTH / 3)) / 2 - 16, 64, "Yes", 10);

			sf::RectangleShape r1;
			r1.setFillColor(sf::Color::Black);
			r1.setOutlineColor(sf::Color::White);
			r1.setOutlineThickness(2);
			r1.setPosition(sf::Vector2f((Window::WIDTH / 3) / 2, Window::HEIGHT / 4));
			r1.setSize(sf::Vector2f(Window::WIDTH - (Window::WIDTH / 3), ye->getY() + ye->getHeight() + 8 - r1.getPosition().y));

			sf::Text title("Exit game?", menuFont, 40);
			title.setPosition(Window::WIDTH / 2 - title.getGlobalBounds().width / 2, Window::HEIGHT / 4 + title.getGlobalBounds().height);

			sf::Text msg("Are you sure you want to exit?", menuFont, 25);
			msg.setPosition(Window::WIDTH / 2 - msg.getGlobalBounds().width / 2, Window::HEIGHT / 4 + 2 * title.getGlobalBounds().height + 35);

			window.draw(r1);
			window.draw(title);
			window.draw(msg);

			for(Gui::Button* b : buttons)
				if(b->getId(90) || b->getId(100))
					b->render(window);
		}
	}
}

void MenuRenderer::renderDebugMenuOverlay(sf::RenderWindow& window) {
	sf::Text enabledNotify("Debug menu enabled", menuFont, 14);
	enabledNotify.setFillColor(sf::Color::White);
	enabledNotify.setOutlineColor(sf::Color::Black);
	enabledNotify.setOutlineThickness(2.0f);
	enabledNotify.setPosition(10, 10);

	window.draw(enabledNotify);

	if(gameState.getGameState(STATE::STATE_GAME_INGAME)) {
		if(gameState.getGameMode(MODE::MODE_INFINITE)) {
			for(int i = 0; i < e.entities.size(); i++) {
				
			}
		}
	}
}

/*		r1.setPosition(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), 16 * wave.getScale());
		r1.setSize(sf::Vector2f((wave.getWindow()->getSize().x / 2 - (32 * wave.getScale())), (wave.getWindow()->getSize().y - (32 * wave.getScale()))));
		*/

void MenuRenderer::playerPos(PlayerEntity* p) {
	if(p->getVelX() > 0) {
		if(p->getBounds().getPosition().x > (wave.getWindow()->getSize().x / 2 + (16 * wave.getScale())) + (wave.getWindow()->getSize().x / 2 - (32 * wave.getScale())) - p->getBounds().getGlobalBounds().width * 2.0) {
			if(isOdd(time)) {
				p->setVelY(5);
				p->setVelX(0);
			} else {
				p->setVelY(-5);
				p->setVelX(-5);
			}
		}
	} 
	if(p->getVelX() < 0) {
		if(p->getBounds().getPosition().x < (wave.getWindow()->getSize().x / 2 + (16 * wave.getScale())) + p->getBounds().getGlobalBounds().width * 2.0) {
			if(isOdd(time)) {
				p->setVelY(5);
				p->setVelX(0);
			} else {
				p->setVelY(-5);
				p->setVelX(5);
			}
		}
	}
	if(p->getVelY() > 0) {
		if(p->getBounds().getPosition().y > (16 * wave.getScale()) + (wave.getWindow()->getSize().y - (32 * wave.getScale())) - p->getBounds().getGlobalBounds().height * 2.0) {
			if(isOdd(time)) {
				p->setVelY(0);
				p->setVelX(-5);
			} else {
				p->setVelY(-5);
				p->setVelX(5);
			}
		}
	} 
	if(p->getVelY() < 0) {
		if(p->getBounds().getPosition().y < 16 * wave.getScale() + p->getBounds().getGlobalBounds().height * 2.0) {
			if(isOdd(time)) {
				p->setVelY(0);
				p->setVelX(-5);
			} else {
				p->setVelY(5);
				p->setVelX(5);
			}
		}
	}
}