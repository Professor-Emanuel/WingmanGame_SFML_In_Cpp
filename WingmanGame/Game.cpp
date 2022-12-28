#include "Game.h"

Game::Game(RenderWindow* window) {
	this->window = window;
	window->setFramerateLimit(60);

	//init textures
	this->playerTexture.loadFromFile("Textures/ship.png");
	this->bulletTexture.loadFromFile("Textures/Guns/missileTex01.png");
	
	//init player
	this->players.push_back(Player(&playerTexture, &bulletTexture));
	this->players.push_back(Player(&playerTexture, &bulletTexture,
		Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L, Keyboard::RShift));

}

Game::~Game() {
	
}

void Game::CombatUpdate() {
	//window bounds
	
}

void Game::Update() {
	for (size_t i = 0; i < this->players.size(); i++) {
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
}

void Game::Draw() {
	this->window->clear();
	for (size_t i = 0; i < this->players.size(); i++) {
		players[i].Draw(*this->window);
	}
	this->window->display();
}