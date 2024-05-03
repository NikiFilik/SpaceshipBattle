#pragma once

#include <SFML/Graphics.hpp>

#include "Object.hpp"
#include "Spaceship.hpp"
#include "TextureHolder.hpp"
#include "Enemy.hpp"
#include "Asteroid.hpp"

namespace nf {
	class Game {
	public:
		sf::RenderWindow mWindow;
		nf::Spaceship mSpaceship;
		nf::TextureHolder mTextureHolder;
		std::vector<nf::Enemy> mEnemies;
		sf::Sprite mBackground;
	private:
		void processInput();
		void processPlayerInput(const sf::Keyboard::Key& key, const bool isPressed);
		void processPlayerInput(const sf::Mouse::Button& button, const bool isPressed);

		void enemySpawn();
		void update(const sf::Time& deltaTime);

		void render();
	public:
		Game();
		void run();
	};
}