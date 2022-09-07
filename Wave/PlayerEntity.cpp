#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(uint32_t x, uint32_t y, ID id, uint32_t uid, sf::Vector2i horizontalBounds, sf::Vector2i verticalBounds, EntityHandler& e, bool overGui, bool controllable, double scale, int32_t renderLayer) : renderLayer(renderLayer), scale(scale), x(x), y(y), id(id), uid(uid), horizontalBounds(horizontalBounds), verticalBounds(verticalBounds), e(e), overGui(overGui), controllable(controllable) {
	if(controllable) {
		for(Entity* entity : e.entities)
			if(entity->getId() == ID::Player)
				secondPlayer = true;
		
		color = secondPlayer ? sf::Color(255, 145, 175, 255) : sf::Color::White; //2nd color is baker-miller pink
	} else {
		color = sf::Color::White;
	}

	health = 0;
}

PlayerEntity::PlayerEntity(uint32_t x, uint32_t y, ID id, uint32_t uid, sf::Vector2i horizontalBounds, sf::Vector2i verticalBounds, EntityHandler& e, bool overGui, bool controllable, int32_t health, double scale, int32_t renderLayer) : renderLayer(renderLayer), scale(scale), x(x), y(y), id(id), uid(uid), horizontalBounds(horizontalBounds), verticalBounds(verticalBounds), e(e), overGui(overGui), controllable(controllable), health(health) {
	if(controllable) {
		for(Entity* entity : e.entities)
			if(entity->getId() == ID::Player)
				secondPlayer = true;
		
		color = secondPlayer ? sf::Color(255, 145, 175, 255) : sf::Color::White; //2nd color is baker-miller pink
	} else {
		color = sf::Color::White;
	}

	std::cout << "Summoned player at coordinates " << x << ", " << y << ".\n";
}

void PlayerEntity::render(sf::RenderWindow& w) {
	if(alive) {
		r.setSize(sf::Vector2f(32 * scale, 32 * scale));
		r.setPosition(x, y);
		r.setFillColor(color);

		w.draw(r);
	}
}

void PlayerEntity::setRenderLayer(int32_t layer) {
	renderLayer = layer;

	for(auto const& t : e.trails)
		if(t.first->getUid() == uid)
			t.first->setRenderLayer(layer);
}

void PlayerEntity::tick() {
	x += velX * scale;
	y += velY * scale;

	if(x >= horizontalBounds.y - 32 * scale)
		setX(horizontalBounds.y - 32 * scale);
	if(x <= horizontalBounds.x)
		setX(horizontalBounds.x);
	if(y >= verticalBounds.y - 32 * scale)
		setY(verticalBounds.y - 32 * scale);
	if(y <= verticalBounds.x)
		setY(verticalBounds.x);

	if(!(velX == 0 && velY == 0))
		e.trails.insert(std::pair<TrailEntity*, Entity*>(new TrailEntity(x, y, id, uid, 25.5f, color, e, scale, renderLayer), this));

	if(controllable && health > 1)
		collision();
}

void PlayerEntity::collision() {
	for(int i = 0; i < e.entities.size(); i++) {
		if(e.entities.at(i)->getBounds().getGlobalBounds().intersects(getBounds().getGlobalBounds())) {
			if(e.entities.at(i)->getId() == ID::BasicEnemy)
				health -= 0.2;
			if(e.entities.at(i)->getId() == ID::FastEnemy)
				health -= 0.35;
			if(e.entities.at(i)->getId() == ID::SmartEnemy)
				health -= 0.5;
		}
	}

	if(health <= 1) {
		health == 0;
		e.die(this);
	}
}

sf::RectangleShape PlayerEntity::getBounds() {
	return r;
}

void PlayerEntity::update() {

}
