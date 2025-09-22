#pragma once
#include "include.h"
class coin
{
public:
	Vector2f position;
	CircleShape shape;
	float size;
	coin();
	coin(Vector2f _position);

	void checkCollision(player& p);
	void update(Time dt);

};

