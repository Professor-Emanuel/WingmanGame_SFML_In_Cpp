#pragma once

#include "Player.h"
#include "Enemy.h"

class Game
{
private:
	//game
	RenderWindow* window;
	float dtMultiplier;
	unsigned score;

	//text
	Font font;
	Text followPlayerText;
	Text staticPlayerText;
	Text enemyText;
	Text gameOverText;
	Text scoreText;

	//bars
	RectangleShape playerExpBar;

	//texttags
	dArr<TextTag> textTags;

	//players
	dArr<Player> players;
	int playersAlive;

	//enemies
	dArr<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	
	//textures
	std::vector<Texture> textures;
	dArr<Texture> enemyTextures;
	dArr<Texture> lWingTextures;
	dArr<Texture> rWingTextures;
	dArr<Texture> cPitTextures;
	dArr<Texture> auraTextures;

public:
	Game(RenderWindow *window);
	virtual ~Game();

	//accessors
	inline RenderWindow& getWindow() {
		return *this->window;
	}

	//setters

	//functions
	void InitTextures();
	void InitUI();
	void UpdateUIPlayer(int index);
	void UpdateUIEnemy(int index);
	//void CombatUpdate();
	void Update(const float& dt);
	void DrawUI();
	void Draw();
};

