#include "Game.h"

int main() {
	RenderWindow window(VideoMode(800, 600), "Wingman Game", Style::Default);
	window.setFramerateLimit(60);

	//game loop
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				window.close();
			}
		}
	}

	return 0;
}