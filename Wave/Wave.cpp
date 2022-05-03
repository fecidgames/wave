#include "Wave.h"

Wave::Wave() : entityHandler(*this), hud(window, entityHandler), menuRenderer(*this, entityHandler, hud, state), inputHandler(*this, menuRenderer, entityHandler) {
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
	menuRenderer.render(window, false);

	entityHandler.render(window, true);
	menuRenderer.render(window, true);

	if(setting_debugMenu)
		menuRenderer.renderDebugMenuOverlay(window); //This must always be on top

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
	loadSettings();
	renderwin(); //Window stuff

	entityHandler.setup();

	loop();

	for(sf::VideoMode mode : sf::VideoMode::getFullscreenModes()) {
		std::cout << mode.isValid() << std::endl;
	}
}

void Wave::renderwin() {
	if(setting_fullscreen) {
		if(sf::VideoMode::getDesktopMode().width > sf::VideoMode::getDesktopMode().height) {
			Window::SCALE = sf::VideoMode::getDesktopMode().width / 1080;
		} else {
			Window::SCALE = sf::VideoMode::getDesktopMode().height / 720;
		}

		Window::WIDTH *= Window::SCALE;
		Window::HEIGHT *= Window::SCALE;
	} else {
		Window::WIDTH  = 1080;
		Window::HEIGHT = 720;
		Window::SCALE = 1;
	}

	std::cout << Window::SCALE << std::endl;
	std::cout << Window::WIDTH << std::endl;
	std::cout << Window::HEIGHT << std::endl;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 6.0;

	if(setting_fullscreen)
		window.create(sf::VideoMode::getDesktopMode(), "Wave! - Release 1.1", sf::Style::Fullscreen, settings);
	else
		window.create(sf::VideoMode((uint32_t) (Window::WIDTH), (uint32_t) (Window::HEIGHT)), "Wave! - Release 1.1", sf::Style::Close | sf::Style::Titlebar, settings);

	window.setFramerateLimit(120);
	
	auto ico = sf::Image();
	ico.loadFromFile("textures/wave.png");

	window.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());
	window.setVerticalSyncEnabled(true);
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
			if(e.type == sf::Event::Closed) {
				if(!menuRenderer.isExitUnconfirmed()) {
					menuRenderer.exitConfirmation();

					if(getGameState().getGameState(STATE::STATE_GAME_INGAME))
						menuRenderer.pauseGame(true);
				}
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

void Wave::stop() {
	saveSettings();
	exit(EXIT_SUCCESS);
}

void Wave::loadSettings() {
	std::ifstream settingsFile;
	settingsFile.open("settings.wv");

	if(!settingsFile.good())
		saveSettings(); //Save default settings

	std::string content;
	std::getline(settingsFile, content);

	std::stringstream toScan(content);
	std::string settingAndValue;
	std::vector<std::string> segments;

	while(std::getline(toScan, settingAndValue, '#'))
		segments.push_back(settingAndValue);

	for(std::string segment : segments) {
		std::stringstream segmentStream(segment);
		std::string setting;
		std::string value;
		std::getline(segmentStream, setting, ':');
		value = segment.substr(2, 3);

		if(setting == "0")
			setting_volume = std::stoi(value);
		if(setting == "1")
			setting_hudSize = std::stoi(value);
		if(setting == "2")
			setting_vSync = (value == "y") ? true : false;
		if(setting == "3")
			setting_fullscreen = (value == "y") ? true : false;
		if(setting == "4")
			setting_menuParticles = (value == "y") ? true : false;
		if(setting == "5")
			setting_debugMenu = (value == "y") ? true : false;
	}
}

void Wave::saveSettings() {
	std::ofstream settingsFile;
	settingsFile.open("settings.wv");
	
	std::string content;
	content.append("0:" + std::to_string(setting_volume));
	content.append("#");
	content.append("1:" + std::to_string(setting_hudSize));
	content.append("#");
	content.append("2:");
	content.append((setting_vSync == true) ? "y" : "n");
	content.append("#");
	content.append("3:");
	content.append((setting_fullscreen == true) ? "y" : "n");
	content.append("#");
	content.append("4:");
	content.append((setting_menuParticles == true) ? "y" : "n");
	content.append("#");
	content.append("5:");
	content.append((setting_debugMenu == true) ? "y" : "n");

	settingsFile << content;
}

void Wave::setVolume(int32_t volume) {
	setting_volume = volume;
}

int32_t Wave::getVolume() {
	return setting_volume;
}

void Wave::setHudSize(int32_t hudSize) {
	setting_hudSize = hudSize;
}

int32_t Wave::getHudSize() {
	return setting_hudSize;
}

void Wave::setVSyncEnabled(bool enabled) {
	setting_vSync = enabled;
	window.setVerticalSyncEnabled(setting_vSync);
}

bool Wave::isVSyncEnabled() {
	return setting_vSync;
}

void Wave::setFullscreenEnabled(bool enabled) {
	setting_fullscreen = enabled;
	
	renderwin();
}

bool Wave::isFullscreenEnabled() {
	return setting_fullscreen;
}

void Wave::setMenuParticlesEnabled(bool enabled) {
	setting_menuParticles = enabled;
}

bool Wave::isMenuParticlesEnabled() {
	return setting_menuParticles;
}

void Wave::setDebugMenuEnabled(bool enabled) {
	setting_debugMenu = enabled;
}

bool Wave::isDebugMenuEnabled() {
	return setting_debugMenu;
}