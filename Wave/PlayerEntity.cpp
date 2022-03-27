#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(float_t x, float_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, bool overGui, bool controllable) : x(x), y(y), id(id), uid(uid), horizontalBounds(horizontalBounds), verticalBounds(verticalBounds), e(e), overGui(overGui), controllable(controllable) {
	if(controllable) {
		for(Entity* entity : e.entities)
			if(entity->getId() == ID::Player)
				secondPlayer = true;
		
		color = secondPlayer ? sf::Color(0xed6fe9) : sf::Color::White; //0xed6fe9 is pink
	} else {
		color = sf::Color::White;
	}

	r.setSize(sf::Vector2f(32, 32));
	r.setPosition(sf::Vector2f(x, y));
	r.setFillColor(color);
}

void PlayerEntity::render(sf::RenderWindow& w) {
	w.draw(r);
}

void PlayerEntity::tick() {
	r.move(sf::Vector2f((velX), (velY)));
	x = r.getPosition().x;
	y = r.getPosition().y;

	if(!(velX == 0 && velY == 0))
		e.trails.insert(std::pair<TrailEntity*, Entity*>(new TrailEntity(x, y, id, uid, 25.5f, color, e), this));
}

sf::RectangleShape PlayerEntity::getBounds() {
	return r;
}
