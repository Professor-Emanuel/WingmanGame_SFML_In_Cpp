#include "Player.h"

unsigned Player::players = 0;

enum controls {UP = 0, DOWN, LEFT, RIGHT, SHOOT};
enum weapons { LASER = 0, MISSILE01, MISSILE02};

Player::Player(std::vector<Texture> &textures,
	int UP, int DOWN, int LEFT, int RIGHT, int SHOOT) 
	:level(1), exp(0), expNext(100), hp(10),
	hpMax(10), damage(1), damageMax(2),
	score(0) 
{
	//dt
	this->dtMultiplier = 62.5f;
	//update positions
	this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;

	//textures and sprites
	this->sprite.setTexture(textures[0]);
	this->sprite.setScale(0.13f, 0.13f);

	this->laserTexture = &textures[1];
	this->missile01Texture = &textures[2];

	this->mainGunSprite.setTexture(textures[3]);
	this->mainGunSprite.setOrigin(
		this->mainGunSprite.getGlobalBounds().width / 2,
		this->mainGunSprite.getGlobalBounds().height / 2);
	this->mainGunSprite.rotate(90);

	this->mainGunSprite.setPosition(this->playerCenter.x + 20.f, this->playerCenter.y);

	//timers
	this->shootTimerMax = 25.f;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 10.f;
	this->damageTimer = this->damageTimerMax;

	//controls
	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;

	//velocity and acceleration
	this->maxVelocity = 25.f;
	this->acceleration = 0.8f;
	this->stabilizerForce = 0.4f;

	//guns
	this->currentWeapon = LASER;

	//upgrades
	this->mainGunLevel = 0;
	this->dualMissile01 = false;
	this->dualMissile02 = false;

	//add number of players for coop
	this->playerNumber = Player::players;
	Player::players++;
}

Player::~Player() {

}

void Player::UpdateAccessories(const float &dt) {
	//set the position of gun to follow player
	this->mainGunSprite.setPosition(this->mainGunSprite.getPosition().x, this->playerCenter.y);

	//update the main gun and correct it after firing
	if (this->mainGunSprite.getPosition().x < this->playerCenter.x + 20) {
		this->mainGunSprite.move(2.f * dt * this->dtMultiplier + 
			this->currentVelocity.x * dt * this->dtMultiplier, 0.f);
	}
	if (this->mainGunSprite.getPosition().x > this->playerCenter.x + 20.f) {
		this->mainGunSprite.setPosition(this->playerCenter.x + 20.f, this->playerCenter.y);
	}
}

void Player::Movement(const float& dt) {

	

	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP]))) {
		this->direction.x = 0.f;
		this->direction.y = -1.f;

		if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
			this->currentVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN]))) {
		this->direction.x = 0.f;
		this->direction.y = 1.f;

		if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
			this->currentVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;
	}
		
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT]))) {
		this->direction.x = -1.f;
		this->direction.y = 0.f;
		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration * dt * this->dtMultiplier;
	}
		
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT]))) {
		this->direction.x = 1.f;
		this->direction.y = 0.f;
		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration * dt * this->dtMultiplier;
	}
		
	//drag force
	if (this->currentVelocity.x > 0) {
		this->currentVelocity.x -= this->stabilizerForce * dt * this->dtMultiplier;

		if (this->currentVelocity.x < 0) {
			this->currentVelocity.x = 0;
		}
	}
	else if (this->currentVelocity.x < 0) {
		this->currentVelocity.x += this->stabilizerForce * dt * this->dtMultiplier;

		if (this->currentVelocity.x > 0) {
			this->currentVelocity.x = 0;
		}
	}

	if (this->currentVelocity.y > 0) {
		this->currentVelocity.y -= this->stabilizerForce * dt * this->dtMultiplier;

		if (this->currentVelocity.y < 0) {
			this->currentVelocity.y = 0;
		}
	}
	else if (this->currentVelocity.y < 0) {
		this->currentVelocity.y += this->stabilizerForce * dt * this->dtMultiplier;

		if (this->currentVelocity.y > 0) {
			this->currentVelocity.y = 0;
		}
	}
		

	//final move
	this->sprite.move(this->currentVelocity.x * dt * this->dtMultiplier, 
		this->currentVelocity.y * dt * this->dtMultiplier);

	//update positions
	this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;
	
}

void Player::Combat(const float& dt) {
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT])) && this->shootTimer >= this->shootTimerMax)
	{
		if (this->currentWeapon == LASER) {
			//create bullet
			if (this->mainGunLevel == 0) {
				this->bullets.push_back(Bullet(laserTexture, Vector2f(this->playerCenter.x + 50, this->playerCenter.y), Vector2f(0.2f, 0.2f), Vector2f(1.f, 0.f), 20.f, 60.f, 5.f));
			}
			else if (this->mainGunLevel == 1) {
				
			}
			else if (this->mainGunLevel == 2) {
				
			}

			//animate gun
			this->mainGunSprite.move(-30.f, 0.f);
		}
		else if (this->currentWeapon == MISSILE01) {
			//create bullet
			this->bullets.push_back(Bullet(missile01Texture, Vector2f(this->playerCenter.x, this->playerCenter.y -25.f), Vector2f(0.05f, 0.05f), Vector2f(1.f, 0.f), 2.f, 50.f, 1.f));

			if (this->dualMissile01) {
				this->bullets.push_back(Bullet(missile01Texture, Vector2f(this->playerCenter.x, this->playerCenter.y + 25.f), Vector2f(0.05f, 0.05f), Vector2f(1.f, 0.f), 2.f, 50.f, 1.f));
			}
		}
		else if (this->currentWeapon == MISSILE02) {
			if (this->dualMissile02) {
			
			}
		}

		this->shootTimer = 0; //reset timer
	}
}

void Player::Update(Vector2u windowBounds, const float& dt) {
	//update timer
	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer += 1.f * dt * this->dtMultiplier;

	if (this->damageTimer < this->damageTimerMax)
		this->damageTimer += 1.f * dt * this->dtMultiplier;

	this->Movement(dt);
	this->UpdateAccessories(dt);
	this->Combat(dt);
}

void Player::Draw(RenderTarget &target) {
	for (size_t i = 0; i < this->bullets.size(); i++) {
		this->bullets[i].Draw(target);
	}

	target.draw(this->mainGunSprite);
	target.draw(this->sprite);
	
}