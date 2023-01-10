#pragma once
#include "Bullet.h"



class Player
{
private:
	float dtMultiplier;
	unsigned playerNumber;

	Vector2f playerCenter;

	Sprite sprite;
	RectangleShape hitBox;

	//accessories
	Sprite mainGunSprite;
	dArr<Bullet> bullets;
	Texture* laserTexture;
	Texture* missile01Texture;
	Texture* missile02Texture;

	dArr<Texture>* lWingTextures;
	dArr<Texture>* rWingTextures;
	dArr<Texture>* cPitTextures;
	dArr<Texture>* auraTextures;
	Sprite lWing;
	Sprite rWing;
	Sprite cPit;
	Sprite aura;

	float shootTimer;
	float damageTimer;
	float shootTimerMax;
	float damageTimerMax;

	int controls[5];
	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
	float stabilizerForce;

	int level;
	int exp;
	int expNext;
	int statPoints;

	int cooling; //endurance
	int plating; //vigor
	int power; //strength
	int wiring; //agility

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
	dArr<Texture>& lWingTextures, dArr<Texture>& rWingTextures, dArr<Texture>& cPitTextures, 
		dArr<Texture>& auraTextures,
		int UP = 22, int DOWN = 18, int LEFT = 0, int RIGHT = 3, int SHOOT = 57);
	virtual ~Player();

	//accessors
	Bullet& getBullet(unsigned index);
	void removeBullet(unsigned index);
	inline const int getBulletsSize() const { return this->bullets.size(); }
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }
	inline const String getHpAsString() const { 
		return std::to_string(this->hp) + "/" + std::to_string(this->hpMax);
	}
	int getDamage() const;
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline const int& getHp() const { return this->hp; }
	inline const int& getHpMax() const { return this->hpMax; }
	inline void takeDamage(int damage) { this->hp -= damage; }
	inline bool isAlive() const { return this->hp > 0; }
	inline const int& getPlayerNr() const { return this->playerNumber; }
	inline const int& getLevel() const { return this->level; }
	inline const int& getExp() const { return this->exp; }
	inline const int& getExpNext() const { return this->expNext; }
	inline bool gainExp(int exp) { 
		this->exp += exp; 
		return this->UpdateLeveling(); 
	}

	//functions
	bool UpdateLeveling();
	void UpdateAccessories(const float& dt);
	void Combat(const float& dt);
	void Movement(const float& dt);
	void Update(Vector2u windowBounds, const float& dt);
	void Draw(RenderTarget& target);
	

	//statics
	static unsigned players;
};

