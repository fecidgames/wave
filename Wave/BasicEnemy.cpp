#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, double scale, int32_t renderLayer) : renderLayer(renderLayer), scale(scale), x(x), y(y), id(id), uid(uid), horizontalBounds(horizontalBounds), verticalBounds(verticalBounds), e(e) {
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
}

void BasicEnemy::render(sf::RenderWindow& w) {
	w.draw(r);
}

void BasicEnemy::setRenderLayer(int32_t layer) {
	renderLayer = layer;

	for(auto const& t : e.trails)
		if(t.first->getUid() == uid)
			t.first->setRenderLayer(layer);
}

void BasicEnemy::tick() {
	sf::Vector2f movementVector(velX, velY);
	float magnitude = std::sqrt(movementVector.x * movementVector.x + movementVector.y * movementVector.y);
	if (magnitude > 5) {
		movementVector.x *= 5 / magnitude;
		movementVector.y *= 5 / magnitude;
	}

	r.move(sf::Vector2f(movementVector.x * scale, movementVector.y * scale));
	x = r.getPosition().x;
	y = r.getPosition().y;

	e.trails.insert(std::pair<TrailEntity*, Entity*>(new TrailEntity((movementVector.x > 0) ? (x + 1) : (x - 1), (movementVector.y > 0) ? (y + 1) : (y - 1), id, uid, 10, sf::Color::Red, e, scale, renderLayer), this));

	if ((x >= horizontalBounds.y - 32 * scale) || (x <= horizontalBounds.x))
		setVelX(-getVelX());
	if ((y >= verticalBounds.y - 32 * scale) || (y <= verticalBounds.x))
		setVelY(-getVelY());
}

sf::RectangleShape BasicEnemy::getBounds() {
	return r;
}

void BasicEnemy::update() {
	r.setSize(sf::Vector2f(32 * scale, 32 * scale));
}