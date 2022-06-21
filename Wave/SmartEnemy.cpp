#include "SmartEnemy.h"

SmartEnemy::SmartEnemy(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, double scale, int32_t renderLayer, int32_t target) : renderLayer(renderLayer), scale(scale), x(x), y(y), id(id), uid(uid), horizontalBounds(horizontalBounds), verticalBounds(verticalBounds), e(e) {
	r.setSize(sf::Vector2f(32 * scale, 32 * scale));
	r.setPosition(sf::Vector2f(x, y));
	r.setFillColor(sf::Color::Red);

	int32_t rand = std::rand()%(6);
	if(isOdd(rand)) {
		velX = 5;
		velY = 5;
	} else {
		velX = -5;
		velY = -5;
	}

	for(Entity* e : e.entities) {
		if(e->getUid() == target && e->getId() == ID::Player)
			this->target = (PlayerEntity*) e;
	}
}

void SmartEnemy::render(sf::RenderWindow& w) {
	w.draw(r);
}

void SmartEnemy::setRenderLayer(int32_t layer) {
	renderLayer = layer;

	for(auto const& t : e.trails)
		if(t.first->getUid() == uid)
			t.first->setRenderLayer(layer);
}

void SmartEnemy::tick() {
	r.move(sf::Vector2f((velX * scale), (velY * scale)));
	x = r.getPosition().x;
	y = r.getPosition().y;

	float diffX = (float) x - (float) target->getX() - 16.0f;
	float diffY = (float) y - (float) target->getY() - 16.0f;
	float dist  = (float) std::sqrt(((x - target->getX()) * (x - target->getX())) + ((y - target->getY()) * (y - target->getY())));

	velX = ((-1.0 / dist) * diffX) * 2.0;
	velY = ((-1.0 / dist) * diffY) * 2.0;

	e.trails.insert(std::pair<TrailEntity*, Entity*>(new TrailEntity((velX > 0) ? (x + 1) : (x - 1), (velY > 0) ? (y + 1) : (y - 1), id, uid, 10, sf::Color::Green, e, scale, renderLayer), this));
}

sf::RectangleShape SmartEnemy::getBounds() {
	return r;
}

PlayerEntity* SmartEnemy::getTarget() {
	return target;
}

void SmartEnemy::update() {
	r.setSize(sf::Vector2f(32.0 * scale, 32.0 * scale));
}