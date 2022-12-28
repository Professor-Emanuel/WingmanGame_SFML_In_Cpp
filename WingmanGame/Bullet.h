#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <vector>

using namespace sf;

class Bullet
{
private:
	Texture* texture;
	Sprite sprite;
	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;

public:
	Bullet(Texture* texture, Vector2f position, Vector2f direction, float initialVelocity, float maxVelocity, float acceleration);
	virtual ~Bullet();

	//accessors
	inline const FloatRect& getGlobalBounds() const {
		return this->sprite.getGlobalBounds();
	}

	inline const Vector2f& getPosition() const {
		return this->sprite.getPosition();
	}

	//functions
	void Movement();

	void Update();
	void Draw(RenderTarget &target);

};

