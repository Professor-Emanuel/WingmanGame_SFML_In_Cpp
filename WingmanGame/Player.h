#pragma once
#include "Bullet.h"



class Player
{
private:
	unsigned playerNumber;
	Vector2f playerCenter;

	Sprite sprite;
	RectangleShape hitBox;

	//accessories
	Sprite mainGunSprite;
	std::vector<Bullet> bullets;
	Texture* laserTexture;
	Texture* missile01Texture;
	Texture* missile02Texture;

	int shootTimer;
	int damageTimer;
	int shootTimerMax;
	int damageTimerMax;
	int controls[5];

	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
	float stabilizerForce;

	int level;
	int exp;
	int expNext;
	int hp;
	int hpMax;
	int score;
	int damage;
	int damageMax;

	int currentWeapon;

	//upgades
	int mainGunLevel;
	bool dualMissile01;
	bool dualMissile02;

public:
	//Player(Texture *texture);
	Player(std::vector<Texture> &textures,
		int UP = 22, int DOWN =18, int LEFT = 0, int RIGHT = 3, int SHOOT = 57);
	virtual ~Player();

	//accessors
	inline std::vector<Bullet>& getBullets() {
		return this->bullets;
	}
	inline const Vector2f& getPosition() const {
		return this->sprite.getPosition();
	}
	inline const String getHpAsString() const {
		return std::to_string(this->hp) + "/" + std::to_string(this->hpMax);
	}

	//functions
	void UpdateAccessories();
	void Combat();
	void Update(Vector2u windowBounds);
	void Draw(RenderTarget& target);
	void Movement();

	//statics
	static unsigned players;
};

