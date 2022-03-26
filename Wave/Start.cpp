#include "Wave.h"

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 6.0;

	Wave wave(settings);
	return 0;
}
