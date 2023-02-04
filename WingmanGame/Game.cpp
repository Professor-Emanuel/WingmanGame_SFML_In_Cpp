#include "Game.h"

enum textures { player = 0, laser01, missile01, mainGun01 };

Game::Game(RenderWindow* window) {
	this->window = window;
	//this->window->setFramerateLimit(60);
	this->dtMultiplier = 62.5f;

	//init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
	
	//init textures
	this->InitTextures();
	
	//init player
	this->players.add(Player(this->textures, this->lWingTextures, this->rWingTextures, 
		this->cPitTextures, this->auraTextures));
	this->players.add(Player(this->textures, this->lWingTextures, this->rWingTextures,
		this->cPitTextures, this->auraTextures,
		Keyboard::Numpad8, Keyboard::Numpad5, 
		Keyboard::Numpad4, Keyboard::Numpad6, Keyboard::Numpad1));

	this->playersAlive = this->players.size();

	/*this->players.push_back(Player(&playerTexture, &bulletTexture,
		Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L, Keyboard::RShift));
		*/
	
	//init enemies
	Enemy e1(this->enemyTextures, this->window->getSize(),
		Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f), 0, rand() % 3 + 1, 3, 1, 
		rand()%this->players.size());
	
	this->enemiesSaved.push_back(Enemy(e1));

	this->enemySpawnTimerMax = 25.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	
	this->InitUI();
}

Game::~Game() {
	
}

void Game::InitTextures() {
	//init textures regular
	this->textures.push_back(Texture());
	this->textures[player].loadFromFile("Textures/ship.png");
	this->textures.push_back(Texture());
	this->textures[laser01].loadFromFile("Textures/Guns/rayTex01.png");
	this->textures.push_back(Texture());
	this->textures[missile01].loadFromFile("Textures/Guns/missileTex01.png");
	this->textures.push_back(Texture());
	this->textures[mainGun01].loadFromFile("Textures/Guns/gun01.png");

	Texture temp;
	temp.loadFromFile("Textures/enemyMoveLeft.png");
	//this->textures.push_back(Texture());
	this->enemyTextures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyFollow.png");
	//this->textures.push_back(Texture());
	this->enemyTextures.add(Texture(temp));

	//init accessory textures
	std::ifstream in;

	in.open("Textures/Accessories/leftwings.txt");
	std::string fileName = "";

	if (in.is_open()) {
		while (getline(in, fileName)) {
			Texture temp;
			temp.loadFromFile(fileName);
			this->lWingTextures.add(Texture(temp));
		}
	}

	in.close();

	in.open("Textures/Accessories/rightwings.txt");
	fileName = "";

	if (in.is_open()) {
		while (getline(in, fileName)) {
			Texture temp;
			temp.loadFromFile(fileName);
			this->rWingTextures.add(Texture(temp));
		}
	}

	in.close();

	in.open("Textures/Accessories/cockpits.txt");
	fileName = "";

	if (in.is_open()) {
		while (getline(in, fileName)) {
			Texture temp;
			temp.loadFromFile(fileName);
			this->cPitTextures.add(Texture(temp));
		}
	}

	in.close();

	in.open("Textures/Accessories/auras.txt");
	fileName = "";

	if (in.is_open()) {
		while (getline(in, fileName)) {
			Texture temp;
			temp.loadFromFile(fileName);
			this->auraTextures.add(Texture(temp));
		}
	}

	in.close();
}

void Game::InitUI() {
	Text tempText;

	//follow text init
	this->followPlayerText.setFont(font);
	this->followPlayerText.setCharacterSize(14);
	this->followPlayerText.setFillColor(Color::White);
	//this->followPlayerText.setString(std::to_string(i));

	//static text init
	this->staticPlayerText.setFont(font);
	this->staticPlayerText.setCharacterSize(14);
	this->staticPlayerText.setFillColor(Color::White);
	//this->staticPlayerText.setString("");

	this->playerExpBar.setSize(Vector2f(90.f, 10.f));
	this->playerExpBar.setFillColor(Color(0.f, 90.f, 200.f, 200.f));

	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(14);
	this->enemyText.setFillColor(Color::White);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setCharacterSize(40);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(this->window->getSize().x/2 - 100.f, this->window->getSize().y / 2);
}

void Game::UpdateUIPlayer(int index) {
	if (index >= this->players.size()) {
		std::cout << "OUT OF BOUNDS! (UPDATEUI)";
	}
	else //follow text
	{
		this->followPlayerText.setPosition(this->players[index].getPosition().x - 25.f,
			this->players[index].getPosition().y - 68.f);
		this->followPlayerText.setString(std::to_string(this->players[index].getPlayerNr()) +
			"								"
			+ this->players[index].getHpAsString() + "\n\n\n\n\n\n\n\n\n\n"
			+ std::to_string(this->players[index].getLevel()));

		// BARS
		this->playerExpBar.setPosition(this->players[index].getPosition().x + 10.f,
			this->players[index].getPosition().y + 115.f);

		this->playerExpBar.setScale(
			(static_cast<float>(this->players[index].getExp()) / this->players[index].getExpNext()), 
			1.f);

		//static text
	}
}

/*
void Game::CombatUpdate() {
	//window bounds
	
}
*/

void Game::UpdateUIEnemy(int index) {
	this->enemyText.setPosition(this->enemies[index].getPosition().x,
		this->enemies[index].getPosition().y - 15.f);
	this->enemyText.setString(std::to_string(this->enemies[index].getHP()) +
		"/" +
		std::to_string(this->enemies[index].getHPMax()));
}

void Game::Update(const float &dt) {

	if (this->playersAlive > 0) {
		//update timers
		if (this->enemySpawnTimer < this->enemySpawnTimerMax) {
			this->enemySpawnTimer += 1.f * dt * this->dtMultiplier;
		}

		//spawn enemies
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->enemies.add(Enemy(this->enemyTextures, this->window->getSize(),
				Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f),
				rand()%2, rand() % 3 + 1, 2, 1, rand()%this->players.size()));

			this->enemySpawnTimer = 0; //reset timer
		}

		for (size_t i = 0; i < this->players.size(); i++) {
			if (this->players[i].isAlive()) {
				//bool enemyRemoved = false;
				//bool bulletRemoved = false;

				//update players
				this->players[i].Update(this->window->getSize(), dt);

				//bullets update
				for (size_t k = 0; k < this->players[i].getBulletsSize(); k++) {
					this->players[i].getBullet(k).Update(dt);

					//enemy collision check
					for (size_t j = 0; j < enemies.size() /* && !enemyRemoved */; j++) {

						if (this->players[i].getBullet(k).getGlobalBounds().
							intersects(this->enemies[j].getGlobalBounds())) {

							this->players[i].removeBullet(k);

							//enemy take damage
							int damage = this->players[i].getDamage();

							if (this->enemies[j].getHP() > 0) {
								this->enemies[j].takeDamage(damage);

								//create text tag
								this->textTags.add(TextTag(&this->font, "-" + 
									std::to_string(damage),
									Color::Red, Vector2f(this->enemies[j].getPosition().x + 20.f,
										this->enemies[j].getPosition().y - 20.f),
									Vector2f(1.f, 0.f), 28, 20.f, true));
							}

							//enemy dead
							if (this->enemies[j].getHP() <= 0) {
								//GAIN EXP
								int exp = this->enemies[j].getHPMax() +
									(rand() % this->enemies[j].getHPMax() + 1);

								//gain score
								int score = this->enemies[j].getHPMax();
								this->players[i].gainScore(score);

								//level up tag
								if (this->players[i].gainExp(exp)) {
									//create text tag
									this->textTags.add(TextTag(&this->font, "LEVEL UP!",
										Color::Cyan, Vector2f(this->players[i].getPosition().x + 20.f,
											this->players[i].getPosition().y - 20.f), 
										Vector2f(0.f, 1.f),
										32, 30.f, true));
								}
							
								this->enemies.remove(j);

								//gain exp tag
								//create text tag
								this->textTags.add(TextTag(&this->font, "+" +
									std::to_string(exp) + " exp",
									Color::Cyan, Vector2f(this->players[i].getPosition().x + 20.f,
										this->players[i].getPosition().y - 20.f), Vector2f(0.f, 1.f),
									24, 25.f, true));
							}
							return;
						}

						else if (this->enemies[i].getPosition().x <
							0 - this->enemies[i].getGlobalBounds().width) {
							this->enemies.remove(i);
							return;
						}
					}

					//window bounds check
					if (/*!bulletRemoved &&*/ this->players[i].getBullet(k).getPosition().x > this->window->getSize().x) {
						this->players[i].removeBullet(k);
						//bulletRemoved = true; 
						return;
					}
				}
			}
		}

		//update enemies
		for (size_t i = 0; i < this->enemies.size(); i++) {

			this->enemies[i].Update(dt, this->players[this->enemies[i].getPlayerFollowNr()].
				getPosition());

			//enemy player collision
			for (size_t k = 0; k < this->players.size(); k++) {
				if (this->players[k].isAlive()) {
					if (this->players[k].getGlobalBounds().intersects(
						this->enemies[i].getGlobalBounds())
						&& !this->players[k].isDamageCooldown()) {

						int damage = this->enemies[i].getDamage();
						this->players[k].takeDamage(damage);

						//create text tag
						this->textTags.add(TextTag(&this->font, "-" + std::to_string(damage),
							Color::Red, Vector2f(this->players[k].getPosition().x + 20.f, 
								this->players[k].getPosition().y - 20.f), Vector2f(-1.f, 0.f),
							30, 20.f, true));

						
						//player death
						if (!this->players[k].isAlive()) {
							this->playersAlive--;
						}

						//this->enemies.remove(i);
						return; //return!!!
					}
				}
			}

			if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width) {
				this->enemies.remove(i);
				return; //return!!!
			}
		}

		//update texttags
		for (size_t i = 0; i < this->textTags.size(); i++) {
			this->textTags[i].Update(dt);

			if (this->textTags[i].getTimer() <= 0.f) {
				this->textTags.remove(i);
				break;
			}
		}
	}
}

void Game::DrawUI() {

	
}

void Game::Draw() {
	this->window->clear();

	//draw player
	for (size_t i = 0; i < this->players.size(); i++) {
		if (this->players[i].isAlive()) {

			this->players[i].Draw(*this->window);
			this->UpdateUIPlayer(i);
			this->window->draw(this->followPlayerText);
			this->window->draw(this->playerExpBar);
		}
	}

	//draw enemies
	for (size_t i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].Draw(*this->window);
		this->UpdateUIEnemy(i);
		this->window->draw(this->enemyText);
	}

	//draw texttags
	for (size_t i = 0; i < this->textTags.size(); i++) {
		this->textTags[i].Draw(*this->window);
	}

	//Game Over Text
	if (this->playersAlive <= 0) {
		this->window->draw(this->gameOverText);
	}

	//this->DrawUI();
	this->window->display();
}