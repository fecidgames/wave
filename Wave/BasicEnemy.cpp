#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e) : x(x), y(y), id(id), uid(uid), horizontalBounds(horizontalBounds), verticalBounds(verticalBounds), e(e) {
	r.setSize(sf::Vector2f(32, 32));
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

void BasicEnemy::tick() {
	r.move(sf::Vector2f((velX), (velY)));
	x = r.getPosition().x;
	y = r.getPosition().y;

	e.trails.insert(std::pair<TrailEntity*, Entity*>(new TrailEntity((velX > 0) ? (x + 1) : (x - 1), (velY > 0) ? (y + 1) : (y - 1), id, uid, 10, sf::Color::Red, e), this));

	if((x >= horizontalBounds.y - 30) || (x <= horizontalBounds.x)) {
		setVelX(-getVelX());
	}
	if((y >= verticalBounds.y - 30) || (y <= verticalBounds.x)) {
		setVelY(-getVelY());
	}
}

sf::RectangleShape BasicEnemy::getBounds() {
	return r;
}