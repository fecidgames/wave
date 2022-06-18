#include "FastEnemy.h"

FastEnemy::FastEnemy(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, double scale, int32_t renderLayer) : renderLayer(renderLayer), scale(scale), x(x), y(y), id(id), uid(uid), horizontalBounds(horizontalBounds), verticalBounds(verticalBounds), e(e) {
	r.setSize(sf::Vector2f(32 * scale, 32 * scale));
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
	r.move(sf::Vector2f((velX * scale), (velY * scale)));
	x = r.getPosition().x;
	y = r.getPosition().y;

	e.trails.insert(std::pair<TrailEntity*, Entity*>(new TrailEntity((velX > 0) ? (x + 1) : (x - 1), (velY > 0) ? (y + 1) : (y - 1), id, uid, 10, sf::Color(242, 202, 90), e, scale, renderLayer), this));

	if((x >= horizontalBounds.y - (32 * scale)) || (x <= horizontalBounds.x)) {
		setVelX(-getVelX());
	}
	if((y >= verticalBounds.y - (32 * scale)) || (y <= verticalBounds.x)) {
		setVelY(-getVelY());
	}
}

void FastEnemy::setRenderLayer(int32_t layer) {
	renderLayer = layer;

	for(auto const& t : e.trails)
		if(t.first->getUid() == uid)
			t.first->setRenderLayer(layer);
}

sf::RectangleShape FastEnemy::getBounds() {
	return r;
}

void FastEnemy::update() {
	r.setSize(sf::Vector2f(32 * scale, 32 * scale));
}
