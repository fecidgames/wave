#include "EntityHandler.h"

EntityHandler::EntityHandler() {
	std::srand(NULL);

	for(int32_t i = 0; i < 15; i++) {
		add(new MenuParticleEntity(std::rand()%Window::WIDTH, std::rand()%Window::HEIGHT, ID::MenuParticle, i, sf::Vector2f(0, Window::WIDTH), sf::Vector2f(0, Window::HEIGHT), *this, false));
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
	}

	for(auto const& t : trails) {
		t.first->tick(dt);
	}
}

void EntityHandler::render(sf::RenderWindow& w, bool afterGui) {
	for(Entity* e : entities) {
		if(!afterGui && !e->renderOverGui())
			e->render(w);
		if(afterGui && e->renderOverGui())
			e->render(w);
	}

	for(auto const& t : trails) {
		if(!afterGui && !t.first->renderOverGui())
			t.first->render(w);
		if(afterGui && t.first->renderOverGui()) 
			t.first->render(w);
	}
}

void EntityHandler::add(Entity* e) {
	entities.insert(entities.begin(), e);
}
