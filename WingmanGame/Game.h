#pragma once

#include "Player.h"

class Game
{
private:
	RenderWindow* window;
	std::vector<Player> players;
	Texture playerTexture;
	Texture bulletTexture;

	Font font;
	std::vector<Text> followPlayerTexts;
	std::vector<Text> staticPlayerTexts;

public:
	Game(RenderWindow *window);
	virtual ~Game();

	//accessors
	inline RenderWindow& getWindow() {
		return *this->window;
	}

	//setters

	//functions
	void InitUI();
	void UpdateUI();
	//void CombatUpdate();
	void Update();
	void DrawUI();
	void Draw();
};

