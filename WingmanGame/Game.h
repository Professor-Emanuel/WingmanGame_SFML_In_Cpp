#pragma once

#include "Player.h"

class Game
{
private:
	RenderWindow* window;
	std::vector<Player> players;
	Texture playerTexture;
	Texture bulletTexture;


public:
	Game(RenderWindow *window);
	virtual ~Game();

	//accessors
	inline RenderWindow& getWindow() {
		return *this->window;
	}

	//setters

	//functions
	void CombatUpdate();
	void Update();
	void Draw();
};

