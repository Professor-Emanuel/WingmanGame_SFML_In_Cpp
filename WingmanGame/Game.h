#pragma once

#include "Player.h"
#include "Enemy.h"

class Game
{
private:
	RenderWindow* window;

	//text
	Font font;
	std::vector<Text> followPlayerTexts;
	std::vector<Text> staticPlayerTexts;
	Text enemyText;
	Text gameOverText;

	//players
	std::vector<Player> players;
	int playersAlive;

	//enemies
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	int enemySpawnTimer;
	int enemySpawnTimerMax;
	
	//textures
	std::vector<Texture> textures;

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

