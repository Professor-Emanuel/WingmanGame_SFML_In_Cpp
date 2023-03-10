#pragma once
#include "TextTag.h"

using namespace sf;

class Bullet
{
private:
	float dtMultiplier;
	Texture* texture;
	Sprite sprite;
	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;

public:
	Bullet(Texture* texture, Vector2f position, Vector2f scale, Vector2f direction, float initialVelocity, float maxVelocity, float acceleration);
	virtual ~Bullet();

	//accessors
	inline const FloatRect& getGlobalBounds() const {
		return this->sprite.getGlobalBounds();
	}

	inline const Vector2f& getPosition() const {
		return this->sprite.getPosition();
	}

	//functions
	void Movement(const float& dt);

	void Update(const float& dt);
	void Draw(RenderTarget &target);

};

