#include "Game.h"

enum textures { player = 0, laser01, missile01, mainGun01, enemy01 };

Game::Game(RenderWindow* window) {
	this->window = window;
	window->setFramerateLimit(60);

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
	/*this->players.push_back(Player(&playerTexture, &bulletTexture,
		Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L, Keyboard::RShift));
		*/
	
	this->enemies.push_back(Enemy(&this->textures[enemy01], this->window->getSize(), 
		Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f), 0, rand() % 3 + 1, 3, 1));

	this->enemies.push_back(Enemy(&this->textures[enemy01], this->window->getSize(),
		Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f), 0, rand() % 3 + 1, 3, 1));

	this->enemies.push_back(Enemy(&this->textures[enemy01], this->window->getSize(),
		Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f), 0, rand() % 3 + 1, 3, 1));

	this->enemies.push_back(Enemy(&this->textures[enemy01], this->window->getSize(),
		Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f), 0, rand() % 3 + 1, 3, 1));
	this->InitUI();
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
	for (size_t i = 0; i < this->players.size(); i++) {
		bool enemyRemoved = false;
		bool bulletRemoved = false;
		//update players
		this->players[i].Update(this->window->getSize());

		//bullets update
		for (size_t k = 0; k < this->players[i].getBullets().size() && !bulletRemoved; k++) {
			this->players[i].getBullets()[k].Update();

			//enemy collision check
			for (size_t j = 0; j < enemies.size() && !enemyRemoved; j++) {

				if (this->players[i].getBullets()[k].getGlobalBounds().
					intersects(this->enemies[j].getGlobalBounds())) {

					this->players[i].getBullets().erase(this->players[i].getBullets().begin() + i);
					this->enemies.erase(this->enemies.begin() + j);
					enemyRemoved = true;
					bulletRemoved = true; 
				}

				else if (this->enemies[i].getPosition().x < 
					0 - this->enemies[i].getGlobalBounds().width) {
					this->enemies.erase(this->enemies.begin() + i);
					enemyRemoved = true; 
				}
			}

			//window bounds check
			if (!bulletRemoved && this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x) {
				this->players[i].getBullets().erase(this->players[i].getBullets().begin() + i);
				bulletRemoved = true; 
			}
		}
	}

	for (size_t i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].Update();
	}

	//update UI
	this->UpdateUI();
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
		this->enemies[i].Draw(*this->window);
	}

	this->DrawUI();
	this->window->display();
}