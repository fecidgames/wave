#include "TrailEntity.h"

TrailEntity::TrailEntity(int32_t x, int32_t y, ID id, uint32_t uid, int32_t life, sf::Color c, EntityHandler& e) : x(x), y(y), id(id), uid(uid), life(life), c(c), e(e) {
	for(Entity* entity : e.entities) {
		if(entity->getUid() == uid && entity->getId() != ID::Trail)
			parent = entity;
	}

	overGui = parent->renderOverGui();
}

void TrailEntity::render(sf::RenderWindow& w) {
	sf::Color col = sf::Color(c.r , c.g, c.b, alpha);
	sf::RectangleShape r;
	r.setPosition(sf::Vector2f(x, y));
	r.setSize(sf::Vector2f(32, 32));
	r.setFillColor(col);

	w.draw(r);
}

void TrailEntity::tick() {
	std::map<Entity*, Entity*>::iterator it;
	it=e.trails.find(this);

	
	alpha -= life;
	if(alpha <= life) {
		alpha = 0;
		e.trails.erase(it);
	}
}

sf::RectangleShape TrailEntity::getBounds() {
	return parent->getBounds();
}