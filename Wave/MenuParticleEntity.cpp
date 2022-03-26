#include "MenuParticleEntity.h"

MenuParticleEntity::MenuParticleEntity(float_t x, float_t y, ID id, uint32_t uid, EntityHandler& e) : x(x), y(y), id(id), uid(uid), e(e), color(std::rand()%(255), std::rand()%(255), std::rand()%(255)) {
	r.setSize(sf::Vector2f(32, 32));
	r.setPosition(sf::Vector2f(x, y));
	r.setFillColor(color);

	int32_t rand = std::rand()%(6);
	velX = std::rand()%(10);
	velY = std::rand()%(10);
}

void MenuParticleEntity::render(sf::RenderWindow& w) {
	w.draw(r);
}

void MenuParticleEntity::tick(sf::Time& dt) {
	r.move(sf::Vector2f((velX), (velY)));

	float_t mov_x = std::abs(r.getPosition().x - x);
	float_t mov_y = std::abs(r.getPosition().y - y);
	float_t moved = (mov_x + mov_y) / 2;

	x = r.getPosition().x;
	y = r.getPosition().y;

	e.trails.insert(std::pair<TrailEntity*, Entity*>(new TrailEntity((velX > 0) ? (x + 1) : (x - 1), (velY > 0) ? (y + 1) : (y - 1), id, uid, 10, color, e), this));
}

sf::RectangleShape MenuParticleEntity::getBounds() {
	return r;
}