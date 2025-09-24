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
	lives = 3;
	speed = 500;
	lasthit = Time::Zero;
}

player::player(Vector2f _position, float _size,int _speed = 500) {
	size = _size;
	position = _position;
	speed = _speed;
	shape.setRadius(size);
	shape.setFillColor(Color::White);
	shape.setOrigin(shape.getGeometricCenter());
	vel = Vector2f(0, 0);
	acc = Vector2f(0, 0);
	mass = 1.0f;
	score = 0;
	lives = 3; 
	lasthit = Time::Zero;
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


void player::update(Time dt, float offset)
{

	if (moveR) {
		position.x += speed * dt.asSeconds();
		moveR = false;	
	}
	if (moveL) {
		position.x -= speed * dt.asSeconds();
		moveL = false;
	}
	if (moveU && onGround) {
		moveU = false;
		onGround = false;
		vel.y = -800;
	}
	shape.setPosition(position);

	if (lives <= 0) {
		position = { offset + 960 , 0 };
		vel = { 0,0 };
		lives = 3;
	}

	if (position.y > 2000) {
		lives = 0;
	}
}	

void player::physicsUpdate(Time dt)
{
	float grav = 981; // Gravity
	acc = Vector2f(0, grav);
	vel = vel + acc * dt.asSeconds();	
	position = position + vel * dt.asSeconds();	

}
void player::takeDamage(Time tt)
{

	float temp = tt.asMilliseconds() - lasthit.asMilliseconds();
	// Define invincibility frame duration
	Time iFrames = milliseconds(500);

	// If the player was hit within the invincibility frame duration, do not reduce lives
	if (temp > iFrames.asMilliseconds()) {
		lives -= 1;
		lasthit = tt;
	}
}

