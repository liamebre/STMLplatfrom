#include "player.h"
#include <iostream>
using namespace std;

player::player() {
	size = 100;
	position = Vector2f(0, 0);
	shape.setRadius(size);
	shape.setFillColor(Color::Red);
	shape.setOrigin(shape.getGeometricCenter());
	vel = Vector2f(0, 0);
	acc = Vector2f(0, 0);
	mass = 1.0f;
	score = 0;
}

player::player(Vector2f _position, float _size) {
	size = _size;
	position = _position;
	shape.setRadius(size);
	shape.setFillColor(Color::White);
	shape.setOrigin(shape.getGeometricCenter());
	vel = Vector2f(0, 0);
	acc = Vector2f(0, 0);
	mass = 1.0f;
	score = 0;
}

void player::setSize(int _size)
{
	size = _size;
	shape.setRadius(size);
}

void player::moveRight()
{
	moveR = true;
}

void player::moveLeft()
{
	moveL = true;
}
void player::moveUp()
{
	moveU= true;
}


void player::update(Time dt)
{

	if (moveR) {
		position.x += 500 * dt.asSeconds();
		moveR = false;	
	}
	if (moveL) {
		position.x -= 500 * dt.asSeconds();
		moveL = false;
	}
	if (moveU && onGround) {
		moveU = false;
		onGround = false;
		vel.y = -800;
	}
	shape.setPosition(position);
}	

void player::physicsUpdate(Time dt)
{
	float grav = 981; // Gravity
	acc = Vector2f(0, grav);
	vel = vel + acc * dt.asSeconds();	
	position = position + vel * dt.asSeconds();	

}	
