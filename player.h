#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
using namespace sf;	

class player
{


public:

	Vector2f position;
	Vector2f vel;
	Vector2f acc;
	float mass;
	float size;
	CircleShape shape;
	bool moveL = false;
	bool moveR = false;
	bool moveU = false;
	bool onGround = false;	
	int score;

	player();
	player(Vector2f _position, float _size);
	void setSize(int size_);
	void moveRight();
	void moveLeft();
	void moveUp();
	void update(Time dt);
	void physicsUpdate(Time dt);

};

