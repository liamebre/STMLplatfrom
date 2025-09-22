#pragma once
#include "include.h"
class ground
{
public:
	Vector2f position;
	RectangleShape shape;
	Vector2f size;

	ground();
	ground(Vector2f _position, Vector2f _size);

	void checkCollision(player& p);	
	void checkEnemyCollision(enemy& e);
	void update(Time dt);
};

