#include "LaserEntity.h"

LaserEntity::LaserEntity(int32_t y, ID id, int32_t uid, PlayerEntity* target, EntityHandler& e, double scale, int32_t renderLayer) : y(y), id(id), uid(uid), target(target), e(e), scale(scale), renderLayer(renderLayer) {
	
}

void LaserEntity::render(sf::RenderWindow& w) { //Currently gradient-testing for the line
	sf::VertexArray skyShape(sf::Quads, 4);
	skyShape[0].position = sf::Vector2f(0, y);
	skyShape[0].color = sf::Color::White;
	skyShape[1].position = sf::Vector2f(50, y);
	skyShape[1].color = sf::Color::White;
	skyShape[2].position = sf::Vector2f(50, 0);
	skyShape[2].color = sf::Color::Red;
	skyShape[3].position = sf::Vector2f(0, 0);
	skyShape[3].color = sf::Color::Red;
	w.draw(skyShape);
}

void LaserEntity::tick() {

}

sf::RectangleShape LaserEntity::getBounds() {
	return r;
}

void LaserEntity::update() {

}
