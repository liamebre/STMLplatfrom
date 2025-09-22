#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "player.h"
#include <iostream>
using namespace sf;
using namespace std;	

class enemy
{
public:
	RectangleShape shape; 
	Vector2f position;
	Vector2f startPos;
	Vector2f size;
	Vector2f vel;
	Vector2f acc;
	int leftBound;
	int rightBound;
	float mass;
	bool moving ;
	int speed;
	enemy();
	enemy(Vector2f _position,int _leftBound, int _rightBound,int _speed);
	void checkCollision(player& p,Time _dt);
	void update(Time dt);
	void physicsUpdate(Time dt);
};

