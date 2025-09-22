#include "enemy.h"

enemy::enemy()
{
	position = Vector2f(0, 0);	
	startPos = position;
	size = Vector2f(75, 75);
	shape.setSize(size);
	shape.setPosition(position);
	shape.setFillColor(Color::Yellow);
	shape.setOrigin(shape.getSize() / 2.0f);
	mass = 1.0f;	
	leftBound = 0;
	rightBound = 0;
	speed = 50;	
	vel = Vector2f(0, 0);
	acc = Vector2f(0, 0);
	moving = false;
}

enemy::enemy(Vector2f _position,int _leftbound, int _rightbound,int _speed = 50)
{
	position = _position;
	startPos = position;
	size = Vector2f(100, 200);
	shape.setSize(size);
	shape.setPosition(position);
	shape.setFillColor(Color::Yellow);
	shape.setOrigin(shape.getSize() / 2.0f);
	mass = 1.0f;
	leftBound = _leftbound;
	rightBound = _rightbound;
	speed = _speed;
	vel = Vector2f(0, 0);
	acc = Vector2f(0, 0);
	moving = true;
}

void enemy::checkCollision(player& p,Time _tt) {
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
			// Resolve collision on the X axis - player takes damage
			p.position.x += fromLeft ? -minOverlapX : minOverlapX;
			p.vel.x = 0; // Stop horizontal movement
			p.takeDamage(_tt); // Take damage on side collisions
		}
		else {
			// Resolve collision on the Y axis - no damage, acts as platform
			p.position.y += fromTop ? -minOverlapY : minOverlapY;
			p.vel.y = 0; // Stop vertical movement
			if (fromTop) {
				p.onGround = true;
				p.moveU = false;
			}
		}
	}
}

void enemy::update(Time dt) {
	if (moving) {
		// Calculate next position before moving
		float nextX = position.x + speed * dt.asSeconds();
		float distanceFromStart = nextX - startPos.x;
		
		// Check bounds and reverse direction if needed
		if (distanceFromStart > rightBound) {
			// Hit right bound, reverse direction
			position.x = startPos.x + rightBound; // Correct to exact bound
			speed = -abs(speed); // Ensure negative speed (moving left)
		}
		else if (distanceFromStart < leftBound) {
			// Hit left bound, reverse direction
			position.x = startPos.x + leftBound; // Correct to exact bound
			speed = abs(speed); // Ensure positive speed (moving right)
		}
		else {
			// Normal movement within bounds
			position.x = nextX;
		}
		shape.setPosition(position);
	}
}

void enemy::physicsUpdate(Time dt)
{
	float grav = 981; // Gravity
	acc = Vector2f(0, grav);
	vel = vel + acc * dt.asSeconds();
	position = position + vel * dt.asSeconds();
}
