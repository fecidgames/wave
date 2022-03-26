#include "EntityHandler.h"

EntityHandler::EntityHandler() {
	std::srand(NULL);

	for(int32_t i = 0; i < 15; i++) {
		add(new MenuParticleEntity(std::rand()%Window::WIDTH, std::rand()%Window::HEIGHT, ID::MenuParticle, 0, *this));
	}
}

EntityHandler::~EntityHandler() {
	for(Entity* e : entities) {
		delete e;
	}
}

void EntityHandler::tick(sf::Time& dt) {
	for(Entity* e : entities) {
		e->tick(dt);
		sf::Vector2f pos;
		if(!(e->getId() == ID::Player)) {
			pos = e->getBounds().getPosition();

			if((pos.x >= Window::WIDTH - 30) || (pos.x <= 0)) {
				e->setVelX(-e->getVelX());
				e->tick(dt);
			}
			if((pos.y >= Window::HEIGHT - 30) || (pos.y <= 0)) {
				e->setVelY(-e->getVelY());
				e->tick(dt);
			}
		}
	}

	for(auto const& t : trails) {
		t.first->tick(dt);
	}
}

void EntityHandler::render(sf::RenderWindow& w) {
	for(Entity* e : entities) {
		e->render(w);
	}

	for(auto const& t : trails) {
		t.first->render(w);
	}
}

void EntityHandler::add(Entity* e) {
	entities.insert(entities.begin(), e);
}
