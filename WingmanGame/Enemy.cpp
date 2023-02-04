#include "Enemy.h"

enum eTypes { MOVELEFT = 0, FOLLOW, FOLLOWFAST, FOLLOWSHOOT, FOLLOWFASTSHOOT};

Enemy::Enemy(dArr<Texture> &textures, Vector2u windowBounds, Vector2f position, 
	Vector2f direction, float maxVelocity, Vector2f scale, int type,
	int hpMax, int damageMax, int damageMin, int playerFollowNr)
{
	this->dtMultiplier = 62.5f;
	this->textures = &textures;
	this->type = type;
	this->sprite.setTexture((*this->textures)[this->type]);
	this->sprite.setScale(scale);
	this->windowBounds = windowBounds;
	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
	);

	this->damageTimerMax = 4.f;
	this->damageTimer = 0.f;

	this->direction = direction;
	this->sprite.setPosition(windowBounds.x, 
		(rand() % windowBounds.y) - this->sprite.getGlobalBounds().height);
	this->maxVelocity = maxVelocity;

	this->hpMax = hpMax;
	this->hp = this->hpMax;
	this->damageMax = damageMax;
	this->damageMin = damageMin;
	this->playerFollowNr = playerFollowNr;
}

Enemy::~Enemy()
{
}

void Enemy::collisionUpdate(const float &dt) {
	if (this->damageTimer > 0.f) {

		this->sprite.setColor(Color::Red);

		this->sprite.move(
			this->maxVelocity * -this->normalizedDir.x * this->damageTimer * dt * dtMultiplier,
			this->maxVelocity * -this->normalizedDir.y * this->damageTimer * dt * dtMultiplier);
	}
	else {
		this->sprite.setColor(Color::White);
	}
}

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;

	this->damageTimer = this->damageTimerMax;

	if (this->hp <= 0) {
		this->hp = 0;
	}
		
}

void Enemy::Update(const float& dt, Vector2f playerPosition)
{
	

	switch (this->type) {
	case MOVELEFT:
		this->sprite.move(this->direction.x * this->maxVelocity * dt * this->dtMultiplier, 
			this->direction.y * this->maxVelocity * dt * this->dtMultiplier);

		this->normalizedDir = normalize(this->direction, vectorLength(this->direction));
		break;

	case FOLLOW:
		if (this->sprite.getPosition().x > playerPosition.x) {
			this->direction.x = playerPosition.x - this->sprite.getPosition().x;
			this->direction.y = playerPosition.y - this->sprite.getPosition().y;
		}

		this->normalizedDir = normalize(this->direction, vectorLength(this->direction));

		if (this->normalizedDir.y > 0.3) {
			this->normalizedDir.y = 0.3;
		}
		else if (this->normalizedDir.y < -0.3) {
			this->normalizedDir.y = -0.3;
		}

		if (this->normalizedDir.x > -0.7) {
			this->normalizedDir.x = -0.7;
		}

		this->sprite.setRotation(atan2(this->normalizedDir.y, this->normalizedDir.x) * 180 / 3.14159265359 + 180);

		this->sprite.move(this->normalizedDir.x * this->maxVelocity * dt * this->dtMultiplier,
			this->normalizedDir.y * this->maxVelocity * dt * this->dtMultiplier);
		break;
	}

	//damaged
	if (this->damageTimer > 0.f) {
		this->damageTimer -= 1.f * dt * dtMultiplier;

		this->sprite.setColor(Color::Red);

		this->sprite.move(
			10.f * -this->normalizedDir.x * this->damageTimer * dt * dtMultiplier, 
			10.f * -this->normalizedDir.y * this->damageTimer * dt * dtMultiplier);
	}
	else {
		this->sprite.setColor(Color::White);
	}

	//collision
	this->collisionUpdate(dt);
	
}

void Enemy::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
}
