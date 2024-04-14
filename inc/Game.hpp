#pragma once

#include <SFML/Graphics.hpp>

#include "Object.hpp"
#include "Spaceship.hpp"

namespace nf {
	class Game {
	private:
		sf::RenderWindow mWindow;
		nf::Spaceship mSpaceship;
	private:
		void processInput();
		void processPlayerInput(const sf::Keyboard::Key& key, const bool isPressed);
		void processPlayerInput(const sf::Mouse::Button& button, const bool isPressed);

		void update(const sf::Time& deltaTime);

		void render();
	public:
		Game();
		void run();
	};
}