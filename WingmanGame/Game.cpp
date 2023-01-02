#include "Game.h"

enum textures { player = 0, laser01, missile01, mainGun01, enemy01 };

Game::Game(RenderWindow* window) {
	this->window = window;
	window->setFramerateLimit(60);
	this->runGame = true;

	//init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.tff");
	

	//init textures
	this->textures.push_back(Texture());
	this->textures[player].loadFromFile("Textures/ship.png");
	this->textures.push_back(Texture());
	this->textures[laser01].loadFromFile("Textures/Guns/rayTex01.png");
	this->textures.push_back(Texture());
	this->textures[missile01].loadFromFile("Textures/Guns/missileTex01.png");
	this->textures.push_back(Texture());
	this->textures[mainGun01].loadFromFile("Textures/Guns/gun01.png");
	this->textures.push_back(Texture());
	this->textures[enemy01].loadFromFile("Textures/enemyFollow.png");
	
	//init player
	this->players.push_back(Player(this->textures));
	this->alivePlayers = this->players.size();
	/*this->players.push_back(Player(&playerTexture, &bulletTexture,
		Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L, Keyboard::RShift));
		*/
	
	Enemy e1(&this->textures[enemy01], this->window->getSize(),
		Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f), 0, rand() % 3 + 1, 3, 1);
	
	this->enemiesSaved.push_back(Enemy(e1));

	this->enemySpawnTimerMax = 20;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	
}

Game::~Game() {
	
}

void Game::InitUI() {
	Text tempText;
	for (size_t i = 0; i < this->players.size(); i++) {
		//follow text init
		tempText.setFont(font);
		tempText.setCharacterSize(14);
		tempText.setFillColor(Color::White);
		tempText.setString(std::to_string(i));

		this->followPlayerTexts.push_back(Text(tempText));

		//static text init
		tempText.setFont(font);
		tempText.setCharacterSize(14);
		tempText.setFillColor(Color::White);
		tempText.setString("");

		this->staticPlayerTexts.push_back(Text(tempText));
	}

	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(14);
	this->enemyText.setFillColor(Color::White);
}

void Game::UpdateUI() {
	for (size_t i = 0; i < this->followPlayerTexts.size(); i++) {
		this->followPlayerTexts[i].setPosition(this->players[i].getPosition().x, this->players[i].getPosition().y - 20.f);
		this->followPlayerTexts[i].setString(std::to_string(i) + "					" + players[i].getHpAsString());
	}

	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++) {
		
	}
}

/*
void Game::CombatUpdate() {
	//window bounds
	
}
*/

void Game::Update() {

	if (this->runGame) {
		//update timers
		if (this->enemySpawnTimer < this->enemySpawnTimerMax) {
			this->enemySpawnTimer++;
		}

		//spawn enemies
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->enemies.push_back(Enemy(&this->textures[enemy01], this->window->getSize(),
				Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f),
				0, rand() % 3 + 1, 3, 1));

			this->enemySpawnTimer = 0; //reset timer
		}

		for (size_t i = 0; i < this->players.size(); i++) {
			//bool enemyRemoved = false;
			//bool bulletRemoved = false;
			
			//update players
			this->players[i].Update(this->window->getSize());

			//bullets update
			for (size_t k = 0; k < this->players[i].getBullets().size() /* && !bulletRemoved*/; k++) {
				this->players[i].getBullets()[k].Update();

				//enemy collision check
				for (size_t j = 0; j < enemies.size() /* && !enemyRemoved */; j++) {

					if (this->players[i].getBullets()[k].getGlobalBounds().
						intersects(this->enemies[j].getGlobalBounds())) {

						this->players[i].getBullets().erase(this->players[i].getBullets().begin() + i);
						if (this->enemies[j].getHP() > 0)
							this->enemies[j].takeDamage(this->players[i].getDamage());
						if (this->enemies[j].getHP() <= 0)
							this->enemies.erase(this->enemies.begin() + j);
						//enemyRemoved = true;
						//bulletRemoved = true; 
						return;
					}

					else if (this->enemies[i].getPosition().x <
						0 - this->enemies[i].getGlobalBounds().width) {
						this->enemies.erase(this->enemies.begin() + i);
						//enemyRemoved = true; 
						return;
					}
				}

				//window bounds check
				if (/*!bulletRemoved &&*/ this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x) {
					this->players[i].getBullets().erase(this->players[i].getBullets().begin() + i);
					//bulletRemoved = true; 
					return;
				}
			}
		}

		//update enemies
		for (size_t i = 0; i < this->enemies.size(); i++) {

			this->enemies[i].Update();

			for (size_t k = 0; k < this->players.size(); k++) {
				if (this->players[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds())) {

					this->players[k].takeDamage(this->enemies[i].getDamage());

					if (!this->players[k].isAlive()) {
						this->players.erase(this->players.begin() + k);
					}

					this->enemies.erase(this->enemies.begin() + i);
					return; //return!!!
				}
			}

			if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width) {
				this->enemies.erase(this->enemies.begin() + i);
				return; //return!!!
			}
		}
		//update UI
		this->UpdateUI();
	}
}

void Game::DrawUI() {
	for (size_t i = 0; i < this->followPlayerTexts.size(); i++) {
		this->window->draw(this->followPlayerTexts[i]);
	}

	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++) {
		this->window->draw(this->staticPlayerTexts[i]);
	}
}

void Game::Draw() {
	this->window->clear();
	for (size_t i = 0; i < this->players.size(); i++) {
		this->players[i].Draw(*this->window);
	}

	for (size_t i = 0; i < this->enemies.size(); i++) {
		this->enemyText.setPosition(this->enemies[i].getPosition());
		this->enemyText.setString(std::to_string(this->enemies[i].getHP()) + 
			"/" + 
			std::to_string(this->enemies[i].getHPMax()));
		this->enemies[i].Draw(*this->window);
		this->window->draw(this->enemyText);
	}

	this->DrawUI();
	this->window->display();
}