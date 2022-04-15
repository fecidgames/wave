#include "Wave.h"

Wave::Wave(sf::ContextSettings settings) : entityHandler(*this), window(sf::VideoMode(Window::WIDTH, Window::HEIGHT), "Wave! - Release 1.1", sf::Style::Close | sf::Style::Titlebar, settings), hud(window, entityHandler), menuRenderer(entityHandler, hud, state), inputHandler(menuRenderer, entityHandler) {
	init();
}

Wave::~Wave() {
	
}

void Wave::tick() {
	entityHandler.tick();
	inputHandler.tick();
}

double startupFadeCol = 250;
void Wave::render() {
	startupFadeCol = (startupFadeCol >= 25) ? (startupFadeCol - 25) : 0;
	window.clear(sf::Color(startupFadeCol, startupFadeCol, startupFadeCol));

	entityHandler.render(window, false);

	menuRenderer.render(window);

	entityHandler.render(window, true);

	window.display();
}

sf::RenderWindow* Wave::getWindow() {
	return &window;
}

GameState& Wave::getGameState() {
	return state;
}

HUD& Wave::getHud() {
	return hud;
}

MenuRenderer& Wave::getMenuRenderer() {
	return menuRenderer;
}

void Wave::init() {
	auto ico = sf::Image();
	ico.loadFromFile("textures/wave.png");

	window.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());
	window.setVerticalSyncEnabled(true);
	loop();
}

void Wave::loop() {
	sf::Clock clock_0;
	sf::Clock clock_1;
	sf::Clock clock_2;
	sf::Time dt = clock_0.restart();
	sf::Time t = clock_1.restart();

	int32_t fps = 0;
	double_t lastTime = dt.asMilliseconds() * 1000;
	double_t ms = 1000000000.0 / 60.0;
	double_t delta = 0.0;
	int32_t timer = t.asMilliseconds();
	while(window.isOpen()) {
		sf::Event e;
		while(window.pollEvent(e)) {
			if(e.type == e.Closed) {
				window.close();
			}

			inputHandler.update(&e);
		}

		double_t now = clock_2.getElapsedTime().asMilliseconds() * 1000;
		delta += (now - lastTime) / ms;
		lastTime = now;

		while(delta >= .0007) {
			tick();
			delta -= .0007;
		}

		if(window.isOpen()) {
			fps++;
			render();
		}
		if(clock_1.restart().asMilliseconds() - timer > 1000) {
			timer += 1000;
			fps = 0;
		}

		dt = clock_0.restart();
	}
}