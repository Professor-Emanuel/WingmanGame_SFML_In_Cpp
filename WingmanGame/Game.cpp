#include "Game.h"

Game::Game(RenderWindow* window) {
	this->window = window;
	window->setFramerateLimit(60);

	//init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.tff");

	//init textures
	this->playerTexture.loadFromFile("Textures/ship.png");
	this->bulletTexture.loadFromFile("Textures/Guns/missileTex01.png");
	this->gunTexture01.loadFromFile("Textures/Guns/gun01.png");
	
	//init player
	this->players.push_back(Player(&playerTexture, &bulletTexture, &gunTexture01));
	/*this->players.push_back(Player(&playerTexture, &bulletTexture,
		Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L, Keyboard::RShift));
		*/
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
		//update players
		this->players[i].Update(this->window->getSize());

		//bullets update
		for (size_t k = 0; k < this->players[i].getBullets().size(); k++) {
			this->players[i].getBullets()[k].Update();
			//window bounds check
			if (this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x) {
				this->players[i].getBullets().erase(this->players[i].getBullets().begin() + i);
				break; //BREAK!!!!!!!!!!!!!!!!!!!!!!!
			}

			//enemy collision check
		}
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
	this->DrawUI();
	this->window->display();
}