#include "MenuRenderer.h"
#include "Wave.h"
#include "LaserEntity.h" //Temporary, delete later!!

MenuRenderer::MenuRenderer(Wave& wave, EntityHandler& e, HUD& hud, GameState& state) : e(e), hud(hud), gameState(state), wave(wave) {
	if(!menuFont.loadFromFile("fonts/mainFont.ttf"))
		throw "[mainFont.ttf] could not be loaded";
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
	time = 0; //Resets time for player AI

	clearLists();

	setupDrawables(gameState);
	setupButtons(gameState);
	setupEntities(gameState);
}

void MenuRenderer::setupInGame(STATE gameState) {
	time = 0;

	clearLists();
	setupDrawables(gameState);
	setupButtons(gameState);
}

void MenuRenderer::resetDrawables() {
	clearLists();

	setupDrawables(gameState.getGameState());
	setupButtons(gameState.getGameState());
}

void MenuRenderer::clearLists() {
	rects.clear();
	texts.clear();

	for(int32_t i = 0; i < buttons.size(); i++) {
		if(!buttons.at(i)->getId(9) && !buttons.at(i)->getId(10) && !buttons.at(i)->getId(99)) {
			delete buttons.at(i);
			buttons.erase(buttons.begin() + i--);
		}
	}
	
	sliders.clear();
	checkboxes.clear();
	arrows.clear();
}

void MenuRenderer::setupDrawables(STATE gameState) {
	double fontMultiplier = (wave.getScale() > 1.6) ? 1.6 : wave.getScale();

	if(gameState == STATE::STATE_MENU_MAIN) {
		texts.insert(texts.begin(), createCenteredTextX(40, "Wave!", 50));
	}

	if(gameState == STATE::STATE_MENU_SELECT) {
		sf::RectangleShape previewField;
		previewField.setPosition(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), 16 * wave.getScale());
		previewField.setSize(sf::Vector2f((wave.getWindow()->getSize().x / 2 - (32 * wave.getScale())), (wave.getWindow()->getSize().y - (32 * wave.getScale()))));
		previewField.setFillColor(sf::Color::Black);
		previewField.setOutlineColor(sf::Color::White);
		previewField.setOutlineThickness(1.0f);

		sf::Text gamemode = createCenteredTextXY("Infinite.", 21 * fontMultiplier, 0);

		arrows.insert(arrows.begin(), new Gui::Arrow(gamemode.getPosition().x - 10, gamemode.getPosition().y, 30, gamemode.getGlobalBounds().height + 6, true, 1));
		arrows.insert(arrows.begin(), new Gui::Arrow(gamemode.getPosition().x + 10 + gamemode.getGlobalBounds().width, gamemode.getPosition().y, 30, gamemode.getGlobalBounds().height + 6, false, 1));

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
		double xOffsetCategory = 50.0 * wave.getScale();
		double xOffsetText = 50.0 * wave.getScale() + 40;

		double scale = wave.getScale() * 0.6 + 0.2;

		double yOffset = 113 * scale;
		double rule = 57 * scale;

		sf::Text title = createCenteredTextX(40, "Options", 50 * scale);

		sf::Text category_sound = createText(xOffsetCategory, yOffset, "Sound options:", 35 * scale);
		sf::Text sound = createText(xOffsetText, yOffset + rule, "Sound enabled:", 30 * scale);
		sf::Text volume = createText(xOffsetText, yOffset + rule * 2, "Volume:", 30 * scale);

		sf::Text category_video = createText(xOffsetCategory, yOffset + rule * 4, "Video settings:", 35 * scale);
		sf::Text vsync = createText(xOffsetText, yOffset + rule * 5, "vSync:", 30 * scale);
		sf::Text fullscreen = createText(xOffsetText, yOffset + rule * 6, "Fullscreen:", 30 * scale);

		sf::Text category_misc = createText(xOffsetCategory, yOffset + rule * 8, "Miscellaneous:", 35 * scale);
		sf::Text menuparticles = createText(xOffsetText, yOffset + rule * 9, "Menu particles:", 30 * scale);
		sf::Text debugmenu = createText(xOffsetText, yOffset + rule * 10, "Debug menu:", 30 * scale);

		texts.insert(texts.begin(), title);

		texts.insert(texts.begin(), category_sound);
		texts.insert(texts.begin(), sound);
		texts.insert(texts.begin(), volume);

		texts.insert(texts.begin(), category_video);
		texts.insert(texts.begin(), vsync);
		texts.insert(texts.begin(), fullscreen);

		texts.insert(texts.begin(), category_misc);
		texts.insert(texts.begin(), menuparticles);
		texts.insert(texts.begin(), debugmenu);


		double cbOffset = menuparticles.getPosition().x + (double) menuparticles.getGlobalBounds().width + 20.0 * wave.getScale();

		checkboxes.insert(checkboxes.begin(), new Gui::Checkbox(cbOffset, sound.getPosition().y + sound.getGlobalBounds().height / 2, scale * 2, wave.isSoundEnabled(), 12));
		checkboxes.insert(checkboxes.begin(), new Gui::Checkbox(cbOffset, vsync.getPosition().y + vsync.getGlobalBounds().height / 2, scale * 2, wave.isVSyncEnabled(), 8));
		checkboxes.insert(checkboxes.begin(), new Gui::Checkbox(cbOffset, fullscreen.getPosition().y + fullscreen.getGlobalBounds().height / 2, scale * 2, wave.isFullscreenEnabled(), 9));
		checkboxes.insert(checkboxes.begin(), new Gui::Checkbox(cbOffset, menuparticles.getPosition().y + menuparticles.getGlobalBounds().height / 2, scale * 2, wave.isMenuParticlesEnabled(), 10));
		checkboxes.insert(checkboxes.begin(), new Gui::Checkbox(cbOffset, debugmenu.getPosition().y + debugmenu.getGlobalBounds().height / 2, scale * 2, wave.isDebugMenuEnabled(), 11));

		double blockSizeMultiplier = (wave.getScale() > 1.7) ? 1.7 : wave.getScale();

		volumeSlider = new Gui::Slider(cbOffset, volume.getPosition().y + volume.getGlobalBounds().height / 2, wave.getWindow()->getSize().x - cbOffset - (16.0 * wave.getScale()), 16 * blockSizeMultiplier, 32 * blockSizeMultiplier, 6);
		volumeSlider->setBlockX(getVolumeX() + volumeSlider->getX());

		sliders.insert(sliders.begin(), volumeSlider);
	}

	if(gameState == STATE::STATE_MENU_GAMEOVER) {
		sf::Text title = createCenteredTextX(40, "Game over", 50);
		sf::Text time = createCenteredTextX(title.getPosition().y + title.getGlobalBounds().height + 30, "Time survived: " + pTime, 25);
		sf::Text points = createCenteredTextX(time.getPosition().y + time.getGlobalBounds().height + 10, "Points collected: " + gameScore, 25);
		sf::Text winner = createCenteredTextX(points.getPosition().y + points.getGlobalBounds().height + 10, "Winner: " + winningPlayer, 25);

		texts.insert(texts.begin(), title);
		texts.insert(texts.begin(), time);
		texts.insert(texts.begin(), points);
		
		if (wave.getGameState().getGameMode(MODE::MODE_DUAL))
			texts.insert(texts.begin(), winner); 
	}

	if (gameState == STATE::STATE_MENU_HELP) {
		sf::Text title = createCenteredTextX(40, "How to play?", 50);

		std::string subtitleString = (this->gameState.getHelpScreen(HELP::SINGLEPLAYER)) ? "Singleplayer" : (this->gameState.getHelpScreen(HELP::DUAL)) ? "Dual" : "Battle";
		sf::Text subtitle = createCenteredTextX(title.getPosition().y + title.getGlobalBounds().height + 10, subtitleString, 25);

		Gui::Arrow* arrowRight = new Gui::Arrow(title.getPosition().x + title.getGlobalBounds().width + 70, title.getPosition().y + 25, 50, 40, false, 2);
		Gui::Arrow* arrowLeft = new Gui::Arrow(title.getPosition().x - 75, title.getPosition().y + 25, 50, 40, true, 3);
		
		texts.insert(texts.begin(), title);
		texts.insert(texts.begin(), subtitle);

		arrows.insert(arrows.begin(), arrowRight);
		arrows.insert(arrows.begin(), arrowLeft);

		//Render the scene
		if (this->gameState.getHelpScreen(HELP::SINGLEPLAYER)) {
			texts.insert(texts.begin(), createCenteredTextXY("Singleplayer help", 30));
		}
		if (this->gameState.getHelpScreen(HELP::DUAL)) {
			texts.insert(texts.begin(), createCenteredTextXY("Dual help", 30));
		}
		if (this->gameState.getHelpScreen(HELP::BATTLE)) {
			texts.insert(texts.begin(), createCenteredTextXY("Battle help", 30));
		}
	}
}

void MenuRenderer::setupEntities(STATE gameState) {
	for(int i = 0; i < e.entities.size(); ++i) {
		if(e.entities.at(i)->getRenderLayer(2) && e.entities.at(i)->getId() == ID::MenuParticle || e.entities.at(i)->getId() == ID::Player) {
			e.entities.at(i)->setRenderLayer(-1);
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
		if(wave.getGameState().getLastState(STATE::STATE_GAME_INGAME))
			e.removeMenuParticles();

		for(int i = 0; i < e.entities.size(); ++i)
			if(e.entities.at(i)->getId() == ID::MenuParticle)
				return;

		if(wave.isMenuParticlesEnabled())
			e.addMenuParticles();
	}

	if(gameState == STATE::STATE_MENU_SELECT) {
		e.add(new MenuParticleEntity(
			wave.getWindow()->getSize().x / 2 + 50, 50, 
			ID::MenuParticle, 16, 

			sf::Vector2f(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), wave.getWindow()->getSize().x - (16 * wave.getScale())), 
			sf::Vector2f(16 * wave.getScale(), wave.getWindow()->getSize().y - (16 * wave.getScale())), 
			
			e, true, wave.getScale(), 2)
		);
		
		e.add(new MenuParticleEntity(
			wave.getWindow()->getSize().x / 3 + wave.getWindow()->getSize().x / 2 - 62, 
			wave.getWindow()->getSize().y / 2, 
			ID::MenuParticle, 16, 
			
			sf::Vector2f(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), wave.getWindow()->getSize().x - (16 * wave.getScale())), 
			sf::Vector2f(16 * wave.getScale(), wave.getWindow()->getSize().y - (16 * wave.getScale())), 
			
			e, true, wave.getScale(), 2)
		);
		
		e.add(new MenuParticleEntity(
			wave.getWindow()->getSize().x - wave.getWindow()->getSize().x / 3, 
			wave.getWindow()->getSize().y - wave.getWindow()->getSize().y / 4, 
			ID::MenuParticle, 16, 
			
			sf::Vector2f(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), wave.getWindow()->getSize().x - (16 * wave.getScale())), 
			sf::Vector2f(16 * wave.getScale(), wave.getWindow()->getSize().y - (16 * wave.getScale())), 
			
			e, true, wave.getScale(), 2)
		);
		
		e.add(new MenuParticleEntity(
			wave.getWindow()->getSize().x - wave.getWindow()->getSize().x / 4, 
			wave.getWindow()->getSize().y / 4, 
			ID::MenuParticle, 16, 
			
			sf::Vector2f(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), wave.getWindow()->getSize().x - (16 * wave.getScale())), 
			sf::Vector2f(16 * wave.getScale(), wave.getWindow()->getSize().y - (16 * wave.getScale())), 
			
			e, true, wave.getScale(), 2)
		);
		
		e.add(new PlayerEntity(
			wave.getWindow()->getSize().x - wave.getWindow()->getSize().x / 4 - 16, 
			wave.getWindow()->getSize().y / 2 - 16, 
			ID::Player, 18, 
			
			sf::Vector2i(wave.getWindow()->getSize().x / 2 + (16 * wave.getScale()), wave.getWindow()->getSize().x - (16 * wave.getScale())),
			sf::Vector2i(16 * wave.getScale(), wave.getWindow()->getSize().y - (16 * wave.getScale())), 
			
			e, true, false, wave.getScale(), 2)
		);
	}

	if(gameState == STATE::STATE_GAME_INGAME) {
		e.entities.clear();
		if(this->gameState.getGameMode() == MODE::MODE_INFINITE) {
			e.add(new PlayerEntity(wave.getWindow()->getSize().x / 2 - (16.0 * wave.getScale()), wave.getWindow()->getSize().y / 2 - (16.0 * wave.getScale()), ID::Player, 17, sf::Vector2i(0, wave.getWindow()->getSize().x), sf::Vector2i(0, wave.getWindow()->getSize().y), e, false, true, hud.getMaxHealth(), wave.getScale(), 0));	
		}
		if(this->gameState.getGameMode() == MODE::MODE_DUAL) {
			e.add(new PlayerEntity(wave.getWindow()->getSize().x / 2 - (16 * wave.getScale()) - (20 * wave.getScale()), wave.getWindow()->getSize().y / 2 - (16 * wave.getScale()), ID::Player, 17, sf::Vector2i(0, wave.getWindow()->getSize().x), sf::Vector2i(0, wave.getWindow()->getSize().y), e, false, true, hud.getMaxHealth(), wave.getScale(), 0));	
			e.add(new PlayerEntity(wave.getWindow()->getSize().x / 2 - (16 * wave.getScale()) + (20 * wave.getScale()), wave.getWindow()->getSize().y / 2 - (16 * wave.getScale()), ID::Player, 18, sf::Vector2i(0, wave.getWindow()->getSize().x), sf::Vector2i(0, wave.getWindow()->getSize().y), e, false, true, hud.getMaxHealth(), wave.getScale(), 0));	
		}
	}
}

void MenuRenderer::setupButtons(STATE gameState) {
	Gui::Button* BACK_BUTTON = new Gui::Button(16 * wave.getScale(), wave.getWindow()->getSize().y - 64 - (16 * wave.getScale()), (380 / 2), 64, "Back", Gui::Button::ID_GLOBAL_BACK, 1);

	if(wave.isDebugMenuEnabled()) {
		bool exists = false;
		for(Gui::Button* b : buttons) {
			if(b->getId(Gui::Button::ID_DEBUG_KILLALL)) {
				exists = true;
				break;
			}
		}

		if(!exists)
			buttons.insert(buttons.begin(), new Gui::Button(16 * wave.getScale(), (16 * wave.getScale()) + 60, (380 / 2), 64, "Kill all players", Gui::Button::ID_DEBUG_KILLALL, 3));
	}

	if(gameState == STATE::STATE_MENU_MAIN) {
		buttons.insert(buttons.begin(), new Gui::Button((wave.getWindow()->getSize().x / 2 - 190), 130, 380, 64, "Gamemodes", Gui::Button::ID_MAIN_GAMEMODES, 1));
		buttons.insert(buttons.begin(), new Gui::Button((wave.getWindow()->getSize().x / 2 - 190), 210, 380, 64, "Options", Gui::Button::ID_MAIN_OPTIONS, 1));
		buttons.insert(buttons.begin(), new Gui::Button((wave.getWindow()->getSize().x / 2 - 190 + 396), 130, 64, 64, "?", Gui::Button::ID_MAIN_HELP, 1));
		buttons.insert(buttons.begin(), new Gui::Button((wave.getWindow()->getSize().x - (380 / 2) - (16 * wave.getScale())), wave.getWindow()->getSize().y - 64 - (16 * wave.getScale()), (380 / 2), 64, "Quit", Gui::Button::ID_MAIN_QUIT, 1));
		buttons.insert(buttons.begin(), new Gui::Button((wave.getWindow()->getSize().x / 2 - 190), 290, 380, 64, "Shop", Gui::Button::ID_MAIN_SHOP, 1));
	}

	if(gameState == STATE::STATE_MENU_SELECT) {
		buttons.insert(buttons.begin(), BACK_BUTTON);
		buttons.insert(buttons.begin(), new Gui::Button(16 * wave.getScale(), wave.getWindow()->getSize().y - 280, (wave.getWindow()->getSize().x / 2) - (32 * wave.getScale()), 64, "Play gamemode", Gui::Button::ID_SELECT_PLAY, 1));
	}

	if(gameState == STATE::STATE_MENU_SETTINGS)
		buttons.insert(buttons.begin(), BACK_BUTTON);
	
	if(gameState == STATE::STATE_MENU_GAMEOVER)
		buttons.insert(buttons.begin(), BACK_BUTTON);

	if(gameState == STATE::STATE_MENU_HELP)
		buttons.insert(buttons.begin(), BACK_BUTTON);
}

void MenuRenderer::setupDebugMenu(bool enabled) {
	if(enabled) {
		buttons.insert(buttons.begin(), new Gui::Button(16 * wave.getScale(), (16 * wave.getScale()) + 50, (380 / 2), 64, "Kill all players", Gui::Button::ID_DEBUG_KILLALL, 3));
	} else {
		for(int i = 0; i < buttons.size(); i++) {
			if(buttons.at(i)->getId(Gui::Button::ID_DEBUG_KILLALL)) {
				buttons.erase(buttons.begin() + i);
				break;
			}
		}
	}
}

int32_t MenuRenderer::getVolumeX() {
	double r = wave.getVolume() / 100.0 * (double) volumeSlider->getLength();
	std::cout << r << std::endl;
	return r;
}

void MenuRenderer::pauseGame(bool paused) {
	if(gamePaused == paused)
		return;

	gamePaused = paused;
	pauseGuiShown = gamePaused;

	pauseGameBase();
}

void MenuRenderer::pauseGame() {
	gamePaused = !gamePaused;
	pauseGuiShown = gamePaused;

	pauseGameBase();
}

void MenuRenderer::pauseGameBase() {
	if (gamePaused) {
		hud.pauseTime();

		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8 - 360, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "Continue", Gui::Button::ID_PAUSE_CONTINUE, 3));
		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "Main menu", Gui::Button::ID_PAUSE_MAINMENU, 3));
		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8 - 360, wave.getWindow()->getSize().y / 2 - 16 - 64, 720 - 16, 64, "Options", Gui::Button::ID_PAUSE_OPTIONS, 3));
	}
	else {
		hud.resumeTime();

		for (int i = 0; i < buttons.size(); i++) {
			if (buttons.at(i)->getId({ Gui::Button::ID_PAUSE_CONTINUE, Gui::Button::ID_PAUSE_MAINMENU, Gui::Button::ID_PAUSE_OPTIONS })) {
				buttons.erase(buttons.begin() + i);
				i--;
			}
		}
	}
}

void MenuRenderer::hidePauseGUI() {
	pauseGuiShown = !pauseGuiShown;
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
		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "No", 90, 4));
		buttons.insert(buttons.begin(), new Gui::Button(wave.getWindow()->getSize().x / 2 + 8 - 360, wave.getWindow()->getSize().y / 2, 360 - 16, 64, "Yes", 91, 4));
	} else {
		for(int i = 0; i < buttons.size(); i++) {
			if(buttons.at(i)->getId(90) || buttons.at(i)->getId(91)) {
				buttons.erase(buttons.begin() + i);
				i--;
			}
		}
	}
}

void MenuRenderer::render(sf::RenderWindow& window, int32_t layer) {
	if(layer == 1) {
		for(sf::Text t : texts)
			window.draw(t);

		for(sf::RectangleShape r : rects)
			window.draw(r);


		renderForLayer(window, layer);
		

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
	}

	//==========================================================//

	if(gamePaused && layer == 2) {
		double btnY = wave.getWindow()->getSize().y / 2;
		double btnHeight = 64;

		sf::RectangleShape pauseBackground;
		pauseBackground.setFillColor(sf::Color::Black);
		pauseBackground.setOutlineColor(sf::Color::White);
		pauseBackground.setOutlineThickness(2); 
		pauseBackground.setPosition(sf::Vector2f(wave.getWindow()->getSize().x / 2 - 360, wave.getWindow()->getSize().y / 4));
		pauseBackground.setSize(sf::Vector2f(720, btnY + btnHeight + 8 - pauseBackground.getPosition().y));

		sf::Text title("Game paused", menuFont, 40);
		title.setPosition(pauseBackground.getPosition().x + pauseBackground.getGlobalBounds().width / 2 - title.getGlobalBounds().width / 2, pauseBackground.getPosition().y + 16);

		if(pauseGuiShown) {
			window.draw(pauseBackground);
			window.draw(title);
		}

		renderForLayer(window, layer);
	}

	if(layer == 3) {
		//This line we want!!!
		sf::Vertex top[] = {
			sf::Vertex(sf::Vector2f(10, 10), sf::Color::Transparent),
			sf::Vertex(sf::Vector2f(160, 10), sf::Color::Transparent),
			sf::Vertex(sf::Vector2f(160, 20), sf::Color::Red),
			sf::Vertex(sf::Vector2f(10, 20), sf::Color::Red)
		};

		sf::Vertex btm[] = {
			sf::Vertex(sf::Vector2f(10, 20), sf::Color::Red),
			sf::Vertex(sf::Vector2f(160, 20), sf::Color::Red),
			sf::Vertex(sf::Vector2f(160, 30), sf::Color::Transparent),
			sf::Vertex(sf::Vector2f(10, 30), sf::Color::Transparent)
		};

		window.draw(top, 4, sf::Quads);
		window.draw(btm, 4, sf::Quads);

		renderForLayer(window, layer);
	}

	if (exitConfirmationPopup) {
		double btnY = wave.getWindow()->getSize().y / 2;
		double btnHeight = 64;

		sf::RectangleShape r1;
		r1.setFillColor(sf::Color::Black);
		r1.setOutlineColor(sf::Color::White);
		r1.setOutlineThickness(2);
		r1.setPosition(sf::Vector2f(wave.getWindow()->getSize().x / 2 - 360, wave.getWindow()->getSize().y / 4));
		r1.setSize(sf::Vector2f(720, btnY + btnHeight + 8 - r1.getPosition().y));

		sf::Text title = createText("Exit game?", 40);
		title.setPosition(wave.getWindow()->getSize().x / 2 - title.getGlobalBounds().width / 2, wave.getWindow()->getSize().y / 4 + title.getGlobalBounds().height);

		sf::Text msg = createCenteredTextX((int)wave.getWindow()->getSize().y / 4 + 2 * (int)title.getGlobalBounds().height + 35, "Are you sure you want to exit?", 25);

		window.draw(r1);
		window.draw(title);
		window.draw(msg);
	}

	if(layer == 4) {
		if (wave.isDebugMenuEnabled()) {
			sf::Text enabledNotify = createText(10, 10, "Debug menu:", 16);
			sf::Text fps = createText(10, (int)enabledNotify.getGlobalBounds().height + 15, "FPS: " + std::to_string(wave.fps()), 14);
			sf::Text scoreNotify = createText(10, (int)fps.getPosition().y + (int)fps.getGlobalBounds().height + 5, "Score: " + std::to_string(e.scoreCount), 16);

			window.draw(enabledNotify);
			window.draw(fps);
			window.draw(scoreNotify);

			bool flag = e.entities.size() > 0;
			for (int i = 0; i < e.entities.size(); i++) {
				std::string _str = e.entities.at(i)->getId(ID::BasicEnemy) ? "ID:BasicEnemy" : e.entities.at(i)->getId(ID::FastEnemy) ? "ID::FastEnemy" : e.entities.at(i)->getId(ID::MenuParticle) ? "ID:MenuParticle" : e.entities.at(i)->getId(ID::Player) ? "ID:Player" : "ID::SmartEnemy";
				sf::Text _t = createText(10, (int)fps.getPosition().y + (int)fps.getGlobalBounds().height + (i * 18) + 120, "E:-NaN", 14);
				_t.setString("E:" + std::to_string(e.entities.at(i)->getUid()) + "#" + _str);

				window.draw(_t);
				flag = true;
			}

			sf::Text tEntities = createText(10, (int)fps.getPosition().y + (int)fps.getGlobalBounds().height + 100, "Entities:", 16);
			sf::Text nEntities = createText(10, (int)fps.getPosition().y + (int)fps.getGlobalBounds().height + 120, "No entities found", 14);

			window.draw(tEntities);

			if (!flag)
				window.draw(nEntities);
		}

		renderForLayer(window, layer);
	}
}

void MenuRenderer::renderForLayer(sf::RenderWindow& window, int32_t layer) {
	for (Gui::Button* b : buttons)
		if (b->getLayer() == layer)
			b->render(window);

	for (Gui::Slider* s : sliders)
		if (s->getLayer() == layer) 
			s->render(window);

	for (Gui::Checkbox* c : checkboxes)
		if(c->getLayer() == layer)
			c->render(window);

	for (Gui::Arrow* a : arrows)
		if(a->getLayer() == layer)
			a->render(window);
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
	sfText.setPosition((int32_t) x, (int32_t) y);

	return sfText;
}

sf::Text MenuRenderer::createCenteredTextX(double y, std::string text, int size) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);
	sfText.setPosition((int32_t) (wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2), (int32_t) y);

	return sfText;
}

sf::Text MenuRenderer::createCenteredTextX(double y, std::string text, int size, int half) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);

	if(half == 0)
		sfText.setPosition((int32_t) (wave.getWindow()->getSize().x / 4 - sfText.getGlobalBounds().width / 2), (int32_t) y);
	if(half == 1)
		sfText.setPosition((int32_t) (wave.getWindow()->getSize().x / 4 + wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2), (int32_t) y);
	if(!(half == 0) && !(half == 1)) {
		std::cout << "Error: Centered text half was neither 0 nor 1, centering it instead.\n";
		sfText.setPosition((int32_t) (wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2), (int32_t) y);
	}

	return sfText;
}

sf::Text MenuRenderer::createCenteredTextY(double x, std::string text, int size) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);
	sfText.setPosition((int32_t) x, (int32_t) (wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2));

	return sfText;
}

sf::Text MenuRenderer::createCenteredTextY(double x, std::string text, int size, int half) {  //0 is top, 1 is bottom
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);

	if(half == 0)
		sfText.setPosition((int32_t) x, (int32_t) (wave.getWindow()->getSize().y / 4 - sfText.getGlobalBounds().height / 2));
	if(half == 1)
		sfText.setPosition((int32_t) x, (int32_t) (wave.getWindow()->getSize().y / 4 + wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2));
	if(!(half == 0) && !(half == 1)) {
		std::cout << "Error: Centered text half was neither 0 nor 1, centering it instead." << std::endl;
		sfText.setPosition((int32_t) x, (int32_t) (wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2));
	}

	return sfText;
}

sf::Text MenuRenderer::createCenteredTextXY(std::string text, int size) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);
	sfText.setPosition((int32_t) (wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2), (int32_t) (wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2));
	return sfText;
}

sf::Text MenuRenderer::createCenteredTextXY(std::string text, int size, int side) { // 0 is left center, 1 is right center, 2 is bottom center, 3 is top center
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);

	if(side == 0)
		sfText.setPosition((int32_t) (wave.getWindow()->getSize().x / 4 - sfText.getGlobalBounds().width / 2), (int32_t) (wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2));
	else if(side == 1)
		sfText.setPosition((int32_t) (wave.getWindow()->getSize().x / 4 + wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2), (int32_t) (wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2));
	else if(side == 2)
		sfText.setPosition((int32_t) (wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2), (int32_t) (wave.getWindow()->getSize().y / 4 + wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2));
	else if(side == 3)
		sfText.setPosition((int32_t) (wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2), (int32_t) (wave.getWindow()->getSize().y / 4 - sfText.getGlobalBounds().height / 2));
	else {
		std::cout << "Error: Text side modifier invalid, centering it instead." << std::endl;
		sfText.setPosition((int32_t) (wave.getWindow()->getSize().x / 2 - sfText.getGlobalBounds().width / 2), (int32_t) (wave.getWindow()->getSize().y / 2 - sfText.getGlobalBounds().height / 2));
	} 

	return sfText;
}

sf::Text MenuRenderer::createText(std::string text, int size) {
	sf::Text sfText(text, menuFont, size);
	sfText.setOutlineColor(sf::Color::Black);
	sfText.setOutlineThickness(2.0f);
	
	return sfText;
}