#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "dArr.h"

using namespace sf;

class TextTag
{
private:

	float dtMultiplier;

	Font* font;
	Text text;

	Vector2f direction;
	float speed;
	float timerMax;
	float timer;
	bool accelarate;

public:
	TextTag(Font* font, std::string text, const Color color, Vector2f position, Vector2f direction,
		unsigned int size, float timerMax, bool accelarate);
	virtual ~TextTag();

	//accessors
	inline const float& getTimer() const { return this->timer; }

	void Update(const float& dt);
	void Draw(RenderTarget& target);
};
