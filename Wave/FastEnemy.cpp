#include "FastEnemy.h"

FastEnemy::FastEnemy(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e) : x(x), y(y), id(id), uid(uid), horizontalBounds(horizontalBounds), verticalBounds(verticalBounds), e(e) {
	r.setSize(sf::Vector2f(32, 32));
	r.setPosition(sf::Vector2f(x, y));
	r.setFillColor(sf::Color(242, 202, 90));

	int32_t rand = std::rand()%(6);
	if(isOdd(rand)) {
		velX = 6;
		velY = 7;
	} else {
		velX = -6;
		velY = -7;
	}
}

void FastEnemy::render(sf::RenderWindow& w) {
	w.draw(r);
}

void FastEnemy::tick() {
	r.move(sf::Vector2f((velX), (velY)));
	x = r.getPosition().x;
	y = r.getPosition().y;

	e.trails.insert(std::pair<TrailEntity*, Entity*>(new TrailEntity((velX > 0) ? (x + 1) : (x - 1), (velY > 0) ? (y + 1) : (y - 1), id, uid, 10, sf::Color(242, 202, 90), e), this));

	if((x >= horizontalBounds.y - 30) || (x <= horizontalBounds.x)) {
		setVelX(-getVelX());
	}
	if((y >= verticalBounds.y - 30) || (y <= verticalBounds.x)) {
		setVelY(-getVelY());
	}
}

sf::RectangleShape FastEnemy::getBounds() {
	return r;
}