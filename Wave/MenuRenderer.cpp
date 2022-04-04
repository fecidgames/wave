#include "MenuRenderer.h"

MenuRenderer::MenuRenderer(EntityHandler& e, HUD& hud) : e(e), hud(hud) {
	if(!menuFont.loadFromFile("fonts/mainFont.ttf")) {
		throw "[mainFont.ttf] could not be loaded";
	}

	setup(STATE::STATE_MENU_MAIN);
}

MenuRenderer::~MenuRenderer() {
	for(Gui::Button* b : buttons) {
		delete b;
	}
}

void MenuRenderer::setup(STATE gameState) {
	setupDrawables(gameState);
	setupButtons(gameState);
	setupEntities(gameState);
}

void MenuRenderer::setupDrawables(STATE gameState) {
	rects.clear();
	texts.clear();
	
	if(gameState == STATE::STATE_MENU_MAIN) {
		sf::Text title("Wave!", menuFont, 50);
		title.setPosition(Window::WIDTH / 2 - title.getGlobalBounds().width / 2, 40);

		texts.insert(texts.begin(), title);
	}

	if(gameState == STATE::STATE_MENU_SELECT) {
		sf::RectangleShape r1;
		r1.setPosition(Window::WIDTH / 2 + 16, 16);
		r1.setSize(sf::Vector2f((Window::WIDTH / 2 - 32), (Window::HEIGHT - 32)));
		r1.setFillColor(sf::Color::Black);
		r1.setOutlineColor(sf::Color::White);
		r1.setOutlineThickness(1.0f);

		rects.insert(rects.begin(), r1);
	}

	if(gameState == STATE::STATE_MENU_SETTINGS) {
		sf::Text title("Options", menuFont, 50);
		title.setPosition(Window::WIDTH / 2 - title.getGlobalBounds().width / 2, 40);

		texts.insert(texts.begin(), title);
	}
}

void MenuRenderer::setupEntities(STATE gameState) {
	time = 0;

	for(int i = 0; i < e.entities.size(); ++i) {
		if(e.entities.at(i)->renderOverGui() && e.entities.at(i)->getId() == ID::MenuParticle || e.entities.at(i)->getId() == ID::Player) {
			e.entities.erase(e.entities.begin() + i);
			i--;
		}
	}

	if(gameState == STATE::STATE_MENU_SELECT) {
		e.add(new MenuParticleEntity(Window::WIDTH / 2 + 50, 50, ID::MenuParticle, 16, sf::Vector2f(Window::WIDTH / 2 + 16, Window::WIDTH / 2 + 16 + Window::WIDTH / 2 - 32), sf::Vector2f(16, Window::HEIGHT - 16), e, true));
		e.add(new MenuParticleEntity(Window::WIDTH / 2 + Window::WIDTH / 2 - 62, Window::HEIGHT / 2, ID::MenuParticle, 16, sf::Vector2f(Window::WIDTH / 2 + 16, Window::WIDTH / 2 + 16 + Window::WIDTH / 2 - 32), sf::Vector2f(16, Window::HEIGHT - 16), e, true));
		e.add(new MenuParticleEntity(Window::WIDTH - Window::WIDTH / 3, Window::HEIGHT - Window::HEIGHT / 4, ID::MenuParticle, 16, sf::Vector2f(Window::WIDTH / 2 + 16, Window::WIDTH / 2 + 16 + Window::WIDTH / 2 - 32), sf::Vector2f(16, Window::HEIGHT - 16), e, true));
		e.add(new MenuParticleEntity(Window::WIDTH - Window::WIDTH / 4, Window::HEIGHT / 4, ID::MenuParticle, 16, sf::Vector2f(Window::WIDTH / 2 + 16, Window::WIDTH / 2 + 16 + Window::WIDTH / 2 - 32), sf::Vector2f(16, Window::HEIGHT - 16), e, true));
		e.add(new PlayerEntity(Window::WIDTH - Window::WIDTH / 4 - 16, Window::HEIGHT / 2 - 16, ID::Player, 18, sf::Vector2i(Window::WIDTH / 2 + 16, Window::WIDTH - 16), sf::Vector2i(16, Window::HEIGHT - 16), e, true, false));
	}

	if(gameState == STATE::STATE_GAME_INGAME) {
		e.entities.clear();
		e.add(new PlayerEntity(Window::WIDTH / 2 - 16, Window::HEIGHT / 2 - 16, ID::Player, 17, sf::Vector2i(0, Window::WIDTH), sf::Vector2i(0, Window::HEIGHT), e, false, true));			
	}
}

void MenuRenderer::setupButtons(STATE gameState) {
	buttons.clear();

	switch(gameState) {
		case STATE::STATE_MENU_MAIN:
			buttons.insert(buttons.begin(), new Gui::Button(Window::WIDTH / 2 - 190, 130, 380, 64, "Gamemodes", 0));
			buttons.insert(buttons.begin(), new Gui::Button(Window::WIDTH / 2 - 190, 210, 380, 64, "Options", 1));
			buttons.insert(buttons.begin(), new Gui::Button(Window::WIDTH / 2 - 190 + 396, 130, 64, 64, "?", 2));
			buttons.insert(buttons.begin(), new Gui::Button(Window::WIDTH - 204, Window::HEIGHT - 80, (380 / 2), 64, "Quit", 3));
			break;
		
		case STATE::STATE_MENU_SELECT:
			buttons.insert(buttons.begin(), new Gui::Button(16, Window::HEIGHT - 80, (380 / 2), 64, "Back", 4));
			buttons.insert(buttons.begin(), new Gui::Button(16, Window::HEIGHT - 280, (Window::WIDTH / 2) - 32, 64, "Play gamemode", 5));
			break;

		case STATE::STATE_MENU_SETTINGS:
			buttons.insert(buttons.begin(), new Gui::Button(16, Window::HEIGHT - 80, (380 / 2), 64, "Back", 4));
	}
}

void MenuRenderer::render(sf::RenderWindow& window) {
	for(Gui::Button* b : buttons)
		b->render(window);

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
}

void MenuRenderer::playerPos(PlayerEntity* p) {
	if(p->getVelX() > 0) {
		if(p->getBounds().getPosition().x > (Window::WIDTH - 16) - std::rand()%130 + 20) {
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
		if(p->getBounds().getPosition().x < (Window::WIDTH / 2 + 16) + std::rand()%130 - 20) {
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
		if(p->getBounds().getPosition().y > (Window::HEIGHT - 16) - std::rand()%130 + 20) {
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
		if(p->getBounds().getPosition().y < (16) + std::rand()%130 - 20) {
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








/*
===========================================================================================================================================================
						######  #    #  #####       ######  ######  ##   ##  ######  ######  #    #  ######  #    #  #######  ######
						#       #    #    #         #       #    #  # # # #  #    #	 #    #	 ##   #  #		 ##   #     #     #
						#   ##  #    #    #         #       #    #  #  #  #  ######	 #    #	 # #  #  ####	 # #  #     #     ######
						#    #  #    #    #         #       #    #  #     #  #       #    #	 #  # #  #		 #  # #     #          #
						######  ######  #####       ######  ######  #     #  #       ######	 #   ##  ######  #   ##     #     ######
===========================================================================================================================================================
*/

Gui::Button::Button(float_t x, float_t y, float_t width, float_t height, std::string text, int32_t id) : x(x), y(y), width(width), height(height), text(text), id(id) {

}

void Gui::Button::render(sf::RenderWindow& window) {
	sf::RectangleShape btnShape(sf::Vector2f(!hover ? width : width + 6, !hover ? height : height + 6));
	btnShape.setPosition(!hover ? x : x - 3, !hover ? y : y - 3);
	btnShape.setOutlineThickness(1.0f);
	btnShape.setFillColor(!down ? sf::Color::Black : sf::Color::White);
	btnShape.setOutlineColor(sf::Color::White);

	sf::Font f;
	f.loadFromFile("fonts/mainFont.ttf");

	sf::Text btnText(text, f, 35);
	while(btnText.getGlobalBounds().width > btnShape.getGlobalBounds().width)
		btnText.setCharacterSize(btnText.getCharacterSize() - 2.5);

	btnText.setPosition((int) (x + (width / 2) - btnText.getGlobalBounds().width / 2), (int) (y + (height / 2) - btnText.getGlobalBounds().height / 2 ) - 3);
	
	window.draw(btnShape);
	window.draw(btnText);
}
