#include "MenuRenderer.h"
#include "Wave.h"

MenuRenderer::MenuRenderer(Wave& wave, EntityHandler& e, HUD& hud, GameState& state) : e(e), hud(hud), gameState(state), wave(wave) {
	
}

MenuRenderer::~MenuRenderer() {
	for(Gui::Button* b : buttons)
		delete &b;
	
	for(Gui::Checkbox* c : checkboxes)
		delete &c;

	for(Gui::Slider* s : sliders)
		delete &s;

	for(Gui::Arrow* a : arrows)
		delete &a;
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
	double fontMultiplier = (wave.getScale() > 1.6) ? 1.6 : wave.getScale();

	if(gameState == STATE::STATE_MENU_MAIN) {
		sf::Text version("v1.1", menuFont, (uint32_t) (15 * wave.getScale()));
		version.setPosition(5, wave.getWindow()->getSize().y - 5 - version.getGlobalBounds().height);

		texts.insert(texts.begin(), createCenteredTextX(40, "Wave!", 50));
		texts.insert(texts.begin(), createText(5, wave.getWindow()->getSize().y - 20, "v1.1", (uint32_t) (15 * wave.getScale())));
	}

	if(gameState == STATE::STATE_MENU_SELECT) {
		sf::RectangleShape previewField;
		previewField.setPosition(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), 16 * wave.getScale());
		previewField.setSize(sf::Vector2f((wave.getWindow()->getSize().x / 2 - (32 * wave.getScale())), (wave.getWindow()->getSize().y - (32 * wave.getScale()))));
		previewField.setFillColor(sf::Color::Black);
		previewField.setOutlineColor(sf::Color::White);
		previewField.setOutlineThickness(1.0f);

		sf::Text gamemode = createCenteredTextXY("Infinite.", 21 * fontMultiplier, 0);

		arrows.insert(arrows.begin(), new Gui::Arrow(gamemode.getPosition().x - 10, gamemode.getPosition().y, 30, gamemode.getGlobalBounds().height + 6, true, 0));
		arrows.insert(arrows.begin(), new Gui::Arrow(gamemode.getPosition().x + 10 + gamemode.getGlobalBounds().width, gamemode.getPosition().y, 30, gamemode.getGlobalBounds().height + 6, false, 0));

		gamemode.setString(gameMode);
		gamemode.setPosition(wave.getWindow()->getSize().x / 4 - gamemode.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 2 - gamemode.getGlobalBounds().height / 2);

		sf::Text desc1 = createText(descriptionr1, 21 * fontMultiplier);
		sf::Text desc2 = createText(descriptionr2, 21 * fontMultiplier);

		desc1.setPosition(wave.getWindow()->getSize().x / 4 - desc1.getGlobalBounds().width / 2, (int32_t) (wave.getWindow()->getSize().y / 2 - desc1.getGlobalBounds().height / 2 - 100));
		desc2.setPosition(wave.getWindow()->getSize().x / 4 - desc2.getGlobalBounds().width / 2, (int32_t) (wave.getWindow()->getSize().y / 2 - desc2.getGlobalBounds().height / 2 - 100 + desc1.getGlobalBounds().height + 5));		

		texts.insert(texts.begin(), createCenteredTextX(10, "Select gamemode", 35 * fontMultiplier, 0));
		texts.insert(texts.begin(), gamemode);
		texts.insert(texts.begin(), desc1);
		texts.insert(texts.begin(), desc2);

		rects.insert(rects.begin(), previewField);
	}

	if(gameState == STATE::STATE_GAME_INGAME) {
		sf::Text pause = createText("[ESC] Pause", 22 * fontMultiplier);
		sf::Text shop = createText("[TAB] Shop", 22 * fontMultiplier);

		pause.setPosition(8, wave.getWindow()->getSize().y - 8 - pause.getGlobalBounds().height);
		shop.setPosition(wave.getWindow()->getSize().x - shop.getGlobalBounds().width - 8, wave.getWindow()->getSize().y - 8 - shop.getGlobalBounds().height);

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
			e.add(new PlayerEntity(wave.getWindow()->getSize().x / 2 - (16 * wave.getScale()), wave.getWindow()->getSize().y / 2 - (16 * wave.getScale()), ID::Player, 17, sf::Vector2i(0, wave.getWindow()->getSize().x), sf::Vector2i(0, wave.getWindow()->getSize().y), e, false, true, hud.getMaxHealth(), wave.getScale()));	
		}
		if(this->gameState.getGameMode() == MODE::MODE_DUAL) {
			e.add(new PlayerEntity(wave.getWindow()->getSize().x / 2 - (16 * wave.getScale()) - (20 * wave.getScale()), wave.getWindow()->getSize().y / 2 - (16 * wave.getScale()), ID::Player, 17, sf::Vector2i(0, wave.getWindow()->getSize().x), sf::Vector2i(0, wave.getWindow()->getSize().y), e, false, true, hud.getMaxHealth(), wave.getScale()));	
			e.add(new PlayerEntity(wave.getWindow()->getSize().x / 2 - (16 * wave.getScale()) + (20 * wave.getScale()), wave.getWindow()->getSize().y / 2 - (16 * wave.getScale()), ID::Player, 17, sf::Vector2i(0, wave.getWindow()->getSize().x), sf::Vector2i(0, wave.getWindow()->getSize().y), e, false, true, hud.getMaxHealth(), wave.getScale()));	
		}
	}

	if(gameState == STATE::STATE_MENU_GAMEOVER) {
	
	}
}

void MenuRenderer::setupButtons(STATE gameState) {
	//LAST BUTTON ID: 11

	if(wave.isDebugMenuEnabled()) {
		bool exists = false;
		for(Gui::Button* b : buttons) {
			if(b->getId(40)) {
				exists = true;
				break;
			}
		}

		if(!exists)
			buttons.insert(buttons.begin(), new Gui::Button(16 * wave.getScale(), (16 * wave.getScale()) + 50, (380 / 2), 64, "Kill all players", 40));
	}

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

	if(gameState == STATE::STATE_MENU_SETTINGS)
		buttons.insert(buttons.begin(), new Gui::Button(16 * wave.getScale(), wave.getWindow()->getSize().y - 64 - (16 * wave.getScale()), (380 / 2), 64, "Back", 4));
	
	if(gameState == STATE::STATE_MENU_GAMEOVER)
		buttons.insert(buttons.begin(), new Gui::Button(16 * wave.getScale(), wave.getWindow()->getSize().y - 64 - (16 * wave.getScale()), (380 / 2), 64, "Menu", 4));
}

void MenuRenderer::setupDebugMenu(bool enabled) {
	if(enabled) {
		buttons.insert(buttons.begin(), new Gui::Button(16 * wave.getScale(), (16 * wave.getScale()) + 50, (380 / 2), 64, "Kill all players", 40));
	} else {
		for(int i = 0; i < buttons.size(); i++) {
			if(buttons.at(i)->getId(40)) {
				buttons.erase(buttons.begin() + i);
				break;
			}
		}
	}
}

void MenuRenderer::pauseGame(bool paused) {
	if(gamePaused == paused)
		return;

	gamePaused = paused;

	if(gamePaused) {
		hud.pauseTime();

		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8 - 360, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "Continue", 9));
		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "Main menu", 10));
		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8 - 360, wave.getWindow()->getSize().y / 2 - 16 - 64, 720 - 16, 64, "Settings", 11));
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

		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8 - 360, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "Continue", 9));
		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "Main menu", 10));
		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8 - 360, wave.getWindow()->getSize().y / 2 - 16 - 64, 720 - 16, 64, "Settings", 11));
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
		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "No", 90));
		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8 - 360, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "Yes", 100));
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
		for(sf::Text t : texts)
			window.draw(t);

		for(sf::RectangleShape r : rects)
			window.draw(r);


		for(Gui::Button* b : buttons)
			if(!b->getId(40))
				b->render(window);

		for(Gui::Slider* s : sliders)
			s->render(window);

		for(Gui::Checkbox* c : checkboxes)
			c->render(window);

		for(Gui::Arrow* a : arrows)
			a->render(window);

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
			Gui::Button* ct = new Gui::Button(wave.getWindow()->getSize().x / 2 + 8 - 360, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "Continue", 9);

			sf::RectangleShape pauseBackground;
			pauseBackground.setFillColor(sf::Color::Black);
			pauseBackground.setOutlineColor(sf::Color::White);
			pauseBackground.setOutlineThickness(2); 
			pauseBackground.setPosition(sf::Vector2f(wave.getWindow()->getSize().x / 2 - 360, wave.getWindow()->getSize().y / 4));
			pauseBackground.setSize(sf::Vector2f(720, ct->getY() + ct->getHeight() + 8 - pauseBackground.getPosition().y));

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
		for(Gui::Button* b : buttons)
			if(b->getId(40))
				b->render(window);

		if(exitConfirmationPopup) {
			Gui::Button* ye = new Gui::Button((wave.getWindow()->getSize().x) / 2 + 8 - 360, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "Yes", 100);

			sf::RectangleShape r1;
			r1.setFillColor(sf::Color::Black);
			r1.setOutlineColor(sf::Color::White);
			r1.setOutlineThickness(2);
			r1.setPosition(sf::Vector2f(wave.getWindow()->getSize().x / 2 - 360, wave.getWindow()->getSize().y / 4));
			r1.setSize(sf::Vector2f(720, ye->getY() + ye->getHeight() + 8 - r1.getPosition().y));

			delete ye;

			sf::Text title = createText("Exit game?", 40);
			title.setPosition(wave.getWindow()->getSize().x / 2 - title.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 4 + title.getGlobalBounds().height);
			
			sf::Text msg = createCenteredTextX(wave.getWindow()->getSize().y / 4 + 2 * title.getGlobalBounds().height + 35, "Are you sure you want to exit?", 25);

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
	sf::Text enabledNotify = createText(10, 10, "Debug menu:", 16);
	sf::Text fps = createText(10, enabledNotify.getGlobalBounds().height + 15, "FPS: " + std::to_string(wave.fps()), 14);

	window.draw(enabledNotify);
	window.draw(fps);

	if(gameState.getGameState(STATE::STATE_GAME_INGAME)) {
		if(gameState.getGameMode(MODE::MODE_INFINITE) || gameState.getGameMode(MODE::MODE_DUAL)) {
			for(int i = 0; i < e.entities.size(); i++) {
				// list all entities in game
			}
		}
	}
}

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

sf::Text MenuRenderer::createText(double x, double y, std::string text, int size) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);
	sfText.setPosition(x, y);

	return sfText;
}

sf::Text MenuRenderer::createCenteredTextX(double y, std::string text, int size) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);
	sfText.setPosition(wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2, y);

	return sfText;
}

sf::Text MenuRenderer::createCenteredTextX(double y, std::string text, int size, int half) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);

	if(half == 0)
		sfText.setPosition(wave.getWindow()->getSize().x / 4 - sfText.getGlobalBounds().width / 2, y);
	if(half == 1)
		sfText.setPosition(wave.getWindow()->getSize().x / 4 + wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2, y);
	if(!(half == 0) && !(half == 1)) {
		std::cout << "Error: Centered text half was neither 0 nor 1, centering it instead.\n";
		sfText.setPosition(wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2, y);
	}

	return sfText;
}

sf::Text MenuRenderer::createCenteredTextY(double x, std::string text, int size) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);
	sfText.setPosition(x, wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2);

	return sfText;
}

sf::Text MenuRenderer::createCenteredTextY(double x, std::string text, int size, int half) {  //0 is top, 1 is bottom
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);

	if(half == 0)
		sfText.setPosition(x, wave.getWindow()->getSize().y / 4 - sfText.getGlobalBounds().height / 2);
	if(half == 1)
		sfText.setPosition(x, wave.getWindow()->getSize().y / 4 + wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2);
	if(!(half == 0) && !(half == 1)) {
		std::cout << "Error: Centered text half was neither 0 nor 1, centering it instead.\n";
		sfText.setPosition(x, wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2);
	}

	return sfText;
}

sf::Text MenuRenderer::createCenteredTextXY(std::string text, int size) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);
	sfText.setPosition(wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2);
	return sfText;
}

sf::Text MenuRenderer::createCenteredTextXY(std::string text, int size, int side) { // 0 is left center, 1 is right center, 2 is bottom center, 3 is top center
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);

	if(side == 0)
		sfText.setPosition(wave.getWindow()->getSize().x / 4 - sfText.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2);
	else if(side == 1)
		sfText.setPosition(wave.getWindow()->getSize().x / 4 + wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2);
	else if(side == 2)
		sfText.setPosition(wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 4 + wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2);
	else if(side == 3)
		sfText.setPosition(wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 4 - sfText.getGlobalBounds().height / 2);
	else {
		std::cout << "Error: Text side modifier invalid, centering it instead.\n";
		sfText.setPosition(wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2);
	}

	return sfText;
}

sf::Text MenuRenderer::createText(std::string text, int size) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);
	
	return sfText;
}