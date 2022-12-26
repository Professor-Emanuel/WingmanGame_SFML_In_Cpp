#include "Game.h"

Game::Game(RenderWindow* window) {
	this->window = window;
	window->setFramerateLimit(60);

	//init textures
	playerTexture.loadFromFile("Textures/ship.png");
	
	//init player
	player = new Player(&this->playerTexture, Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L, Keyboard::LShift);
}

Game::~Game() {
	delete player;
}

void Game::Update() {
	player->Update();
}

void Game::Draw() {
	window->clear();
	player->Draw(*window);
	window->display();
}