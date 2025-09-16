#include "ground.h"

ground::ground() {
	position = Vector2f(0, 0);
	size = Vector2f(1920, 50);
	shape.setSize(size);
	shape.setFillColor(Color::Green);
	shape.setOrigin(shape.getSize() / 2.0f);
	shape.setPosition(position);
}

ground::ground(Vector2f _position, Vector2f _size) {
	position = _position;
	size = _size;
	shape.setSize(size);
	shape.setFillColor(Color::Green);
	shape.setOrigin(shape.getSize() / 2.0f);
	shape.setPosition(position);
}

void ground::checkCollision(player& p)
{
	if (p.position.y + p.size >= position.y - size.y / 2.0f &&
		p.position.y - p.size <= position.y + size.y / 2.0f &&
		p.position.x + p.size >= position.x - size.x / 2.0f &&
		p.position.x - p.size <= position.x + size.x / 2.0f) {
		// Collision detected, resolve it
		float overlapLeft = (p.position.x + p.size) - (position.x - size.x / 2.0f);
		float overlapRight = (position.x + size.x / 2.0f) - (p.position.x - p.size);
		float overlapTop = (p.position.y + p.size) - (position.y - size.y / 2.0f);
		float overlapBottom = (position.y + size.y / 2.0f) - (p.position.y - p.size);
		bool fromLeft = abs(overlapLeft) < abs(overlapRight);
		bool fromTop = abs(overlapTop) < abs(overlapBottom);
		float minOverlapX = fromLeft ? overlapLeft : overlapRight;
		float minOverlapY = fromTop ? overlapTop : overlapBottom;
		if (abs(minOverlapX) < abs(minOverlapY)) {
			// Resolve collision on the X axis
			p.position.x += fromLeft ? -minOverlapX : minOverlapX;
			p.vel.x = 0; // Stop horizontal movement
		}
		else {
			// Resolve collision on the Y axis
			p.position.y += fromTop ? -minOverlapY : minOverlapY;
			p.vel.y = 0; // Stop vertical movement
			if (fromTop) {
				p.onGround = true;
				p.moveU = false;
			}
		}
	}
	
}

void ground::update(Time dt) {
	shape.setPosition(position);
}

