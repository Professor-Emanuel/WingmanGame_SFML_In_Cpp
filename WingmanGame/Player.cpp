#include "Player.h"

enum controls {UP = 0, DOWN, LEFT, RIGHT, SHOOT};

Player::Player(Texture* texture, int UP, int DOWN, int LEFT, int RIGHT, int SHOOT) 
	:level(1), exp(0), expNext(100), hp(10),
	hpMax(10), damage(1), damageMax(2),
	score(0) 
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);

	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;
}

Player::~Player() {

}

void Player::Movement() {
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP])))
		std::cout << "W" << "\n";
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN])))
		std::cout << "S" << "\n";
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT])))
		std::cout << "A" << "\n";
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT])))
		std::cout << "D" << "\n";
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT])))
		std::cout << "SPACE" << "\n";

}

void Player::Update() {
	this->Movement();
}

void Player::Draw(RenderTarget &target) {
	target.draw(this->sprite);
}