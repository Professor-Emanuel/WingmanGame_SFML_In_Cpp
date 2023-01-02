#include "Player.h"

unsigned Player::players = 0;

enum controls {UP = 0, DOWN, LEFT, RIGHT, SHOOT};

Player::Player(std::vector<Texture> &textures,
	int UP, int DOWN, int LEFT, int RIGHT, int SHOOT) 
	:level(1), exp(0), expNext(100), hp(10),
	hpMax(10), damage(1), damageMax(2),
	score(0) 
{
	this->sprite.setTexture(textures[0]);
	this->sprite.setScale(0.13f, 0.13f);

	this->bulletTexture = &textures[1];

	this->mainGunSprite.setTexture(textures[2]);
	this->mainGunSprite.setOrigin(
		this->mainGunSprite.getGlobalBounds().width / 2,
		this->mainGunSprite.getGlobalBounds().height / 2);
	this->mainGunSprite.rotate(90);

	this->shootTimerMax = 25;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 10;
	this->damageTimer = this->damageTimerMax;

	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;

	this->maxVelocity = 25.f;
	this->acceleration = 0.8f;
	this->stabilizerForce = 0.4f;

	//add number of players for coop
	this->playerNumber = Player::players;
	Player::players++;
}

Player::~Player() {

}

void Player::UpdateAccessories() {
	//set the position of gun to follow player
	this->mainGunSprite.setPosition(this->mainGunSprite.getPosition().x, this->playerCenter.y);

	//update the main gun and correct it after firing
	if (this->mainGunSprite.getPosition().x < this->playerCenter.x + 20) {
		this->mainGunSprite.move(2.f + this->currentVelocity.x, 0.f);
	}
	if (this->mainGunSprite.getPosition().x > this->playerCenter.x + 20.f) {
		this->mainGunSprite.setPosition(this->playerCenter.x + 20.f, this->playerCenter.y);
	}
}

void Player::Movement() {

	

	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP]))) {
		this->direction.x = 0.f;
		this->direction.y = -1.f;

		if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
			this->currentVelocity.y += this->direction.y * this->acceleration;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN]))) {
		this->direction.x = 0.f;
		this->direction.y = 1.f;

		if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
			this->currentVelocity.y += this->direction.y * this->acceleration;
	}
		
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT]))) {
		this->direction.x = -1.f;
		this->direction.y = 0.f;
		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}
		
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT]))) {
		this->direction.x = 1.f;
		this->direction.y = 0.f;
		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}
		
	//drag force
	if (this->currentVelocity.x > 0) {
		this->currentVelocity.x -= this->stabilizerForce;

		if (this->currentVelocity.x < 0) {
			this->currentVelocity.x = 0;
		}
	}
	else if (this->currentVelocity.x < 0) {
		this->currentVelocity.x += this->stabilizerForce;

		if (this->currentVelocity.x > 0) {
			this->currentVelocity.x = 0;
		}
	}

	if (this->currentVelocity.y > 0) {
		this->currentVelocity.y -= this->stabilizerForce;

		if (this->currentVelocity.y < 0) {
			this->currentVelocity.y = 0;
		}
	}
	else if (this->currentVelocity.y < 0) {
		this->currentVelocity.y += this->stabilizerForce;

		if (this->currentVelocity.y > 0) {
			this->currentVelocity.y = 0;
		}
	}
		

	//final move
	this->sprite.move(this->currentVelocity.x, this->currentVelocity.y);

	//update positions
	this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;
	
}

void Player::Combat() {
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT])) && this->shootTimer >= this->shootTimerMax)
	{
		this->bullets.push_back(Bullet(bulletTexture, Vector2f(this->playerCenter.x + 50, this->playerCenter.y), Vector2f(1.f, 0.f), 2.f,50.f, 1.f));

		//animate gun
		this->mainGunSprite.move(-30.f, 0.f);

		this->shootTimer = 0; //reset timer
	}
}

void Player::Update(Vector2u windowBounds) {
	//update timer
	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer++;

	if (this->damageTimer < this->damageTimerMax)
		this->damageTimer++;

	this->Movement();
	this->UpdateAccessories();
	this->Combat();
}

void Player::Draw(RenderTarget &target) {
	for (size_t i = 0; i < this->bullets.size(); i++) {
		this->bullets[i].Draw(target);
	}

	target.draw(this->mainGunSprite);
	target.draw(this->sprite);
	
}