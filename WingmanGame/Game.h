#pragma once

#include "Player.h"

class Game
{
private:
	RenderWindow* window;
public:
	Game(RenderWindow *window);
	virtual ~Game();

	//accessors
	inline RenderWindow& getWindow() {
		return *this->window;
	}

	//setters

	//functions
	void Update();
	void Draw();
};

