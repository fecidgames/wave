#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(uint32_t x, uint32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, bool overGui, bool controllable) : x(x), y(y), id(id), uid(uid), horizontalBounds(horizontalBounds), verticalBounds(verticalBounds), e(e), overGui(overGui), controllable(controllable) {
	if(controllable) {
		for(Entity* entity : e.entities)
			if(entity->getId() == ID::Player)
				secondPlayer = true;
		
		color = secondPlayer ? sf::Color(0xed6fe9) : sf::Color::White; //0xed6fe9 is pink
	} else {
		color = sf::Color::White;
	}

	std::cout << "Player created: " << x << ", " << y << "\n";

	oldX = x;
	oldY = y;
}

void PlayerEntity::render(sf::RenderWindow& w) {
	r.setSize(sf::Vector2f(32, 32));
	r.setPosition(x, y);
	r.setFillColor(color);

	w.draw(r);
}

void PlayerEntity::tick() {
	x += velX;
	y += velY;

	std::cout << "Player ticked: " << x << ", " << y << "\n";

	if(x >= horizontalBounds.y - 30)
		setX(oldX);
	if(y >= verticalBounds.y - 30)
		setY(oldY);

	if(x >= horizontalBounds.y - 30)
		setX(horizontalBounds.y - 30);
	if(x <= horizontalBounds.x)
		setX(horizontalBounds.x);
	if(y >= verticalBounds.y - 30)
		setY(verticalBounds.y - 30);
	if(y <= verticalBounds.x)
		setY(verticalBounds.x);

	if(!(velX == 0 && velY == 0))
		e.trails.insert(std::pair<TrailEntity*, Entity*>(new TrailEntity(x, y, id, uid, 25.5f, color, e), this));

	oldX = x;
	oldY = y;
}

sf::RectangleShape PlayerEntity::getBounds() {
	return r;
}
