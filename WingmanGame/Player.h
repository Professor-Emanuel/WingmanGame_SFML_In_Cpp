#pragma once
#include "Bullet.h"



class Player
{
private:
	unsigned playerNumber;
	Texture* texture;
	Sprite sprite;
	RectangleShape hitBox;

	std::vector<Bullet> bullets;
	Texture* bulletTexture;

	int shootTimer;
	int damageTimer;
	int shootTimerMax;
	int damageTimerMax;
	int controls[5];
	int level;
	int exp;
	int expNext;
	int hp;
	int hpMax;
	int score;
	int damage;
	int damageMax;

public:
	//Player(Texture *texture);
	Player(Texture* texture, Texture* bulletTexture, int UP = 22, int DOWN =18, int LEFT = 0, int RIGHT = 3, int SHOOT = 57);
	virtual ~Player();

	//accessors
	inline std::vector<Bullet>& getBullets() {
		return this->bullets;
	}

	//functions
	void Combat();
	void Update(Vector2u windowBounds);
	void Draw(RenderTarget& target);
	void Movement();

	//statics
	static unsigned players;
};

