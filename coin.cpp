#include "coin.h"

coin::coin()
{
	position = { 0,0 };
	size = 25.0f;
}

coin::coin(Vector2f position_) {
	position = position_;
	size = 25.0f;
	shape.setRadius(size);
	shape.setFillColor(Color::Red);
	shape.setOrigin(shape.getGeometricCenter());
	shape.setPosition(position);
}

void coin::checkCollision(player& p)
{
	Vector2f distance = { p.position - position };
	if (abs(distance.x) <= p.size + size && abs(distance.y) <= p.size +size) {
		p.score += 1; 
		position = { 0,-100 };
	}
}
void coin::update(Time dt_) {
	shape.setPosition(position);
}
