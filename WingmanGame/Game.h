#pragma once

#include "Player.h"
#include "Enemy.h"

class Game
{
private:
	RenderWindow* window;
	float dtMultiplier;

	//text
	Font font;
	Text followPlayerText;
	Text staticPlayerText;
	Text enemyText;
	Text gameOverText;

	RectangleShape playerExpBar;

	//players
	std::vector<Player> players;
	int playersAlive;

	//enemies
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	
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
	void UpdateUIPlayer(int index);
	void UpdateUIEnemy(int index);
	//void CombatUpdate();
	void Update(const float& dt);
	void DrawUI();
	void Draw();
};

