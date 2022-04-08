#include "EntityHandler.h"

EntityHandler::EntityHandler() {
	std::srand(NULL);

	addMenuParticles();
}

EntityHandler::~EntityHandler() {
	for(Entity* e : entities) {
		delete e;
	}
}

void EntityHandler::tick() {
	for(Entity* e : entities) {
		e->tick();
	}

	for(auto const& t : trails) {
		t.first->tick();
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

void EntityHandler::addMenuParticles() {
	for(int32_t i = 0; i < 15; i++)
		add(new MenuParticleEntity(std::rand()%(Window::WIDTH - 50), std::rand()%(Window::HEIGHT - 50), ID::MenuParticle, i, sf::Vector2f(0, Window::WIDTH), sf::Vector2f(0, Window::HEIGHT), *this, false));
}

void EntityHandler::add(Entity* e) {
	entities.insert(entities.begin(), e);
}
