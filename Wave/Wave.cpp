#include "Wave.h"

Wave::Wave() : soundHandler(), entityHandler(*this), hud(window, entityHandler), menuRenderer(*this, entityHandler, hud, state), inputHandler(*this, menuRenderer, entityHandler) {
	init();
}

Wave::~Wave() {
	
}

void Wave::tick() {
	entityHandler.tick();
	inputHandler.tick();
}

void Wave::render() {
	startupFadeCol = (startupFadeCol >= 25) ? (startupFadeCol - 25) : 0;
	window.clear(sf::Color(startupFadeCol, startupFadeCol, startupFadeCol));

	//We have 4 current render layers
	for(int32_t i = 0; i < 5; i++) {
		entityHandler.render(window, i);
		menuRenderer.render(window, i);
	}

	window.display();
}

sf::RenderWindow* Wave::getWindow() {
	return &window;
}

EntityHandler& Wave::getEntityHandler() {
	return entityHandler;
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

	soundHandler.playMusic(0);
	soundHandler.loopMusic(0);
	soundHandler.updateVolume(setting_volume);

	entityHandler.setup();
	menuRenderer.setup(STATE::STATE_MENU_MAIN);

	loop();
}

void Wave::renderwin() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 6.0;

	if(setting_fullscreen)
		window.create(sf::VideoMode::getDesktopMode(), "Wave! - Release 1.1", sf::Style::Fullscreen, settings);
	else
		window.create(sf::VideoMode((uint32_t) (Window::WIDTH), (uint32_t) (Window::HEIGHT)), "Wave! - Release 1.1", sf::Style::Close | sf::Style::Titlebar, settings);

	if(setting_fullscreen) {
		if(window.getSize().x > window.getSize().y) {
			scale = window.getSize().x / 1080.0;
		} else {
			scale = window.getSize().y / 720.0;
		}
	} else scale = 1.0;

	std::cout << "[Window Frame Info]\n";
	std::cout << "Scale:  " << std::to_string(scale) << std::endl;
	std::cout << "Width:  " << window.getSize().x << std::endl;
	std::cout << "Height: " << window.getSize().y << std::endl;
	std::cout << std::endl; 

	if(entityHandler.isSetup()) {
		entityHandler.removeMenuParticles();
		entityHandler.addMenuParticlesWithPreviousColor();
	}
	
	auto ico = sf::Image();
	ico.loadFromFile("textures/wave.png");

	window.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());
	window.setVerticalSyncEnabled(true);

	entityHandler.update();

	if(entityHandler.isSetup())
		menuRenderer.setup(getGameState().getGameState());
}

void Wave::loop() {
	sf::Clock clock_0;
	sf::Clock clock_2;
	sf::Clock clock_3;

	sf::Time dt = clock_0.restart();
	sf::Time prevTime = clock_3.getElapsedTime();
	sf::Time currentTime;

	double_t lastTime = (double) dt.asMilliseconds() * 1000.0;
	double_t ms = 1000000000.0 / 60.0;
	double_t delta = 0.0;
	while(window.isOpen()) {
		sf::Event e;
		while(window.pollEvent(e)) {
			if(e.type == sf::Event::Closed) {
				if(!menuRenderer.isExitUnconfirmed()) {
					if(getGameState().getGameState(STATE::STATE_GAME_INGAME))
						menuRenderer.pauseGame(true);

					menuRenderer.exitConfirmation();
				}
			}

			inputHandler.update(&e);
		}

		double_t now = (double) clock_2.getElapsedTime().asMilliseconds() * 1000.0;
		delta += (now - lastTime) / ms;
		lastTime = now;

		while(delta >= .0007) {
			tick();
			delta -= .0007;
		}

		render();

		currentTime = clock_3.getElapsedTime();
		framesPerSecond = floor((uint32_t) (1.0f / (currentTime.asSeconds() - prevTime.asSeconds())));
		prevTime = currentTime;

		dt = clock_0.restart();
	}
}

void Wave::stop() {
	saveSettings();
	exit(EXIT_SUCCESS);
}

void Wave::loadSettings() { //load saved total score and send to menuRenderer
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
			setting_vSync = (value == "y");
		if(setting == "2")
			setting_fullscreen = (value == "y");
		if(setting == "3")
			setting_menuParticles = (value == "y");
		if(setting == "4")
			setting_debugMenu = (value == "y");
	}
}

void Wave::saveSettings() { //save MenuRenderer's total_score uint32_t
	std::ofstream settingsFile;
	settingsFile.open("settings.wv");
	
	std::string content;
	content.append("0:" + std::to_string(setting_volume));
	content.append("#");
	content.append("1:");
	content.append((setting_vSync) ? "y" : "n");
	content.append("#");
	content.append("2:");
	content.append((setting_fullscreen) ? "y" : "n");
	content.append("#");
	content.append("3:");
	content.append((setting_menuParticles) ? "y" : "n");
	content.append("#");
	content.append("4:");
	content.append((setting_debugMenu) ? "y" : "n");
	content.append("#");
	content.append("4:");
	content.append("0"); // Points

	settingsFile << content;
}

void Wave::setVolume(int32_t volume) {
	setting_volume = volume;
	soundHandler.updateVolume(setting_volume);
}

int32_t Wave::getVolume() {
	return setting_volume;
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
	menuRenderer.setupDebugMenu(enabled);
}

bool Wave::isDebugMenuEnabled() {
	return setting_debugMenu;
}