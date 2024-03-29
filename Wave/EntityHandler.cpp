#include "EntityHandler.h"
#include "Wave.h"

EntityHandler::EntityHandler(Wave& wave) : wave(wave) {
	
}

EntityHandler::~EntityHandler() {
	for(Entity* e : entities)
		delete &e;

	for(auto const& t : trails)
		delete &t.first;
}

void EntityHandler::setup() {
	std::srand(NULL);

	hasBeenSetup = true;

	if(wave.isMenuParticlesEnabled())
		addMenuParticles();
}

int scoreTimer = 0;
void EntityHandler::tick() {
	for(Entity* e : entities)
		if(!wave.getMenuRenderer().isGamePaused() || e->getId(ID::MenuParticle))
			e->tick();

	for(auto const& t : trails)
		if(!wave.getMenuRenderer().isGamePaused() || t.first->getId(ID::MenuParticle))
			t.first->tick();

	if(!wave.getMenuRenderer().isGamePaused()) {
		if(wave.getGameState().getGameState(STATE::STATE_GAME_INGAME)) {
			spawnTimer++;
			scoreTimer++;

			if (scoreTimer >= 15) {
				scoreTimer = 0;
				scoreCount++;
			}

			tickSpawner(spawnTimer);
			return;
		}
	}

	if(!wave.getGameState().getGameState(STATE::STATE_GAME_INGAME))
		spawnTimer = 0;
}

void EntityHandler::update() {
	for(Entity* e : entities)
		e->update();
}

void EntityHandler::render(sf::RenderWindow& w, int32_t layer) {
	for(Entity* e : entities)
		if(e->getRenderLayer(layer))
			e->render(w);

	for(auto const& t : trails)
		if(t.first->getRenderLayer(layer))
			t.first->render(w);
}

void EntityHandler::hideHostileEntities() {
	for(Entity* e : entities)
		if(e->getId(ID::BasicEnemy) || e->getId(ID::FastEnemy) || e->getId(ID::MeteorShowerParticle) || e->getId(ID::SmartEnemy)) {
			e->setRenderLayer(e->getRenderLayer() >= 0 ? -1 : 0);
			std::cout << "Set render layer of E:" << e->getUid() << " to " << e->getRenderLayer() << std::endl;
		}
}

void EntityHandler::hidePlayer() {
	for(Entity* e : entities)
		if(e->getId(ID::Player)) {
			e->setRenderLayer(e->getRenderLayer() >= 0 ? -1 : 0);
			std::cout << "Set render layer of E:" << e->getUid() << " to " << e->getRenderLayer() << std::endl;
		}
}

void EntityHandler::hideParticles() {
	for(Entity* e : entities)
		if(e->getId(ID::MenuParticle)) {
			e->setRenderLayer(e->getRenderLayer() >= 0 ? -1 : 0);
			std::cout << "Set render layer of E:" << e->getUid() << " to " << e->getRenderLayer() << std::endl;
		}
}

void EntityHandler::hideMeteors() {
	for(Entity* e : entities)
		if(e->getId(ID::MeteorShowerParticle)) {
			e->setRenderLayer(e->getRenderLayer() >= 0 ? -1 : 0);
			std::cout << "Set render layer of E:" << e->getUid() << " to " << e->getRenderLayer() << std::endl;
		}
}

void EntityHandler::addMenuParticles() {
	addMenuParticles(0);
}

void EntityHandler::addMenuParticles(int32_t layer) {
	for(int32_t i = 0; i < 15; i++)
		add(new MenuParticleEntity(std::rand()%(wave.getWindow()->getSize().x - 100), std::rand()%(wave.getWindow()->getSize().y - 50), ID::MenuParticle, i, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, false, wave.getScale(), layer));
}

void EntityHandler::addMenuParticlesWithPreviousColor() {
	int32_t i = 0;
	for(sf::Color color : colors) {
		i++;
		add(new MenuParticleEntity(std::rand()%(wave.getWindow()->getSize().x - 100), std::rand()%(wave.getWindow()->getSize().y - 50), ID::MenuParticle, i, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, false, wave.getScale(), color, 0));
	}
}

void EntityHandler::removeMenuParticles() {
	colors.clear();

	for(int32_t i = 0; i < entities.size(); i++)
		if(entities.at(i)->getId() == ID::MenuParticle) {
			colors.insert(colors.begin(), entities.at(i)->getColor());

			delete entities.at(i);

			entities.erase(entities.begin() + i);
			i--;
		}
}

void EntityHandler::add(Entity* e) {
	entities.insert(entities.begin(), e);
}

void EntityHandler::die(PlayerEntity* player) {
	bool shouldEnd = false;

	if (wave.getGameState().getGameMode(MODE::MODE_INFINITE)) {
		for (int i = 0; i < entities.size(); i++) {
			if (entities.at(i)->getId() == ID::Player) {
				PlayerEntity* p = (PlayerEntity*)entities.at(i);
				if (shouldEnd = (p == player)) {
					p->setAlive(false);
					break;
				}
			}
		}
	}

	if (wave.getGameState().getGameMode(MODE::MODE_DUAL)) {
		std::string winningPlayer = "";

		for (int i = 0; i < entities.size(); i++) {
			if (entities.at(i)->getId() == ID::Player) {
				PlayerEntity* p = (PlayerEntity*)entities.at(i);
				if (p == player) {
					p->setAlive(false);
					winningPlayer = (p->isPlayerOne()) ? "Player 1" : "Player 2";
					break;
				}
			}
		}

		shouldEnd = true;
		for (Entity* e : entities)
			if (e->getId() == ID::Player)
				if(((PlayerEntity*)e)->isAlive())
					shouldEnd = false;

		if (shouldEnd)
			wave.getMenuRenderer().setWinningPlayer(winningPlayer);
	}

	if (shouldEnd) {
		for (int i = 0; i < entities.size(); i++) {
			entities.erase(entities.begin() + i);
			--i;
		}

		scoreTimer = 0;
		wave.getHud().stopTime();
		wave.getMenuRenderer().sendTime(wave.getHud().getTimer().getElapsedMilliseconds(), !wave.getGameState().getGameMode(MODE::MODE_INFINITE));
		wave.getMenuRenderer().sendScore(scoreCount);
		wave.getMenuRenderer().gameEnd();

		scoreCount = 0;
	}
}

int tempTimeLoop = 0;
int newWaitTime = 300;
void EntityHandler::tickSpawner(int32_t time) {
	uint32_t uid = 28 + time;

	if(time == 1) {
		add(new BasicEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::BasicEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0));
	}
	if(time == 300) {
		add(new BasicEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::BasicEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0));
	}
	if(time == 600) {
		add(new BasicEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::BasicEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0));
		add(new FastEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::FastEnemy, uid + 1, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0));
	}

	if(time == 900) {
		add(new SmartEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::SmartEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0, 17));
		if(wave.getGameState().getGameMode(MODE::MODE_DUAL))
			add(new SmartEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::SmartEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0, 18));

		add(new FastEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::FastEnemy, uid + 1, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0));
	}
}
