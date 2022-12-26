#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

using namespace sf;

class Player
{
private:
	Texture* texture;
	Sprite shape;
	RectangleShape hitBox;
	int level;
	int exp;
	int expNext;
	int HP;
	int hpMax;
	int score;
	int damage;
	int damageMax;

public:
	Player();
	virtual ~Player();

	void Update();
	void Draw();
};

