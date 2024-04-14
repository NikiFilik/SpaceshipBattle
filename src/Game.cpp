#include "Game.hpp"

namespace nf {
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	Game::Game(): mWindow(sf::VideoMode(1920, 1080), "Spaceship Battle", sf::Style::Fullscreen) {
		mWindow.setVerticalSyncEnabled(true);

		mSpaceship.setup(nf::Vector2f(960.f, 540.f), nf::Vector2f(0.f, 0.f), 48.f, 1, "media/textures/spaceship.png",
			500.f, 1000.f, 1500.f, sf::Keyboard::W, sf::Mouse::Left, sf::Keyboard::Space);
	}

	void Game::run() {
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time timeSinceLastFrame = sf::Time::Zero;

		while (mWindow.isOpen()){
			timeSinceLastUpdate = clock.restart();
			timeSinceLastFrame += timeSinceLastUpdate;

			processInput();

			update(timeSinceLastUpdate);

			if (timeSinceLastFrame >= TimePerFrame) {
				timeSinceLastFrame = sf::Time::Zero;
				render();
			}
		}
	}

	void Game::processInput() {
		sf::Event event;
		while (mWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				processPlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				processPlayerInput(event.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				processPlayerInput(event.mouseButton.button, true);
				break;
			case sf::Event::MouseButtonReleased:
				processPlayerInput(event.mouseButton.button, false);
				break;
			}
		}
	}

	void Game::processPlayerInput(const sf::Keyboard::Key& key, const bool isPressed) {
		if (key == sf::Keyboard::Escape && isPressed) {
			mWindow.close();
		}
		if (key == mSpaceship.getBoostKey()) {
			mSpaceship.setIsBoosting(isPressed);
		}
	}
	void Game::processPlayerInput(const sf::Mouse::Button& button, const bool isPressed) {
		if (button == mSpaceship.getAttackButton() && isPressed) {
			mSpaceship.shoot();
		}
	}

	void Game::update(const sf::Time& deltaTime) {
		mSpaceship.update(deltaTime);
	}

	void Game::render() {
		mWindow.clear();
		mWindow.draw(mSpaceship.getSprite());
		for (int i = 0; i < mSpaceship.getBullets().size(); i++) {
			mWindow.draw(mSpaceship.getBullets()[i].getSprite());
		}
		mWindow.display();
	}
}