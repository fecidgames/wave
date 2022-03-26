#include "Wave.h"

Wave::Wave(sf::ContextSettings settings) : window(sf::VideoMode(Window::WIDTH, Window::HEIGHT), "Wave! - Release 1.1", sf::Style::Close | sf::Style::Titlebar, settings), menuRenderer(), inputHandler(menuRenderer), entityHandler() {
	//Load stuff
	init();
}

Wave::~Wave() {
	
}

void Wave::tick(sf::Time& dt) {
	entityHandler.tick(dt);
}

double startupFadeCol = 250;
void Wave::render(sf::Time& dt) {
	startupFadeCol = (startupFadeCol >= 25) ? (startupFadeCol - 25) : 0;
	window.clear(sf::Color(startupFadeCol, startupFadeCol, startupFadeCol));

	entityHandler.render(window);
	menuRenderer.render(window);

	window.display();
}

sf::RenderWindow* Wave::getWindow() {
	return &window;
}

void Wave::init() {
	auto ico = sf::Image();
	ico.loadFromFile("textures/wave.png");

	window.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());
	window.setVerticalSyncEnabled(true);
	loop();
}

void Wave::loop() {
	sf::Clock clock0;
	sf::Clock clock1;
	sf::Clock clock2;
	sf::Time dt = clock0.restart();
	sf::Time t = clock1.restart();

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

		double_t now = clock2.getElapsedTime().asMilliseconds() * 1000;
		delta += (now - lastTime) / ms;
		lastTime = now;

		std::cout << delta << "\n";

		while(delta >= .0007) {
			tick(dt);
			delta -= .0007;
		}

		if(window.isOpen()) {
			fps++;
			render(dt);
		}
		if(clock1.restart().asMilliseconds() - timer > 1000) {
			timer += 1000;
			fps = 0;
		}

		dt = clock0.restart();
	}
}