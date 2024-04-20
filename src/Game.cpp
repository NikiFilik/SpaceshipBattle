#include "Game.hpp"

#include "globalConstsAndVars.hpp"

namespace nf {
	Game::Game(): mWindow(sf::VideoMode(WindowWidth, WindowHeight), "Spaceship Battle", sf::Style::Fullscreen)
	{
		mWindow.setVerticalSyncEnabled(true);

		mTextureHolder.load(SpaceshipTextureName);
		mTextureHolder.load(SpaceshipBulletTextureName);
		mTextureHolder.load(EnemyTextureName);

		mSpaceship.setup(SpaceshipStartPosition, SpaceshipStartSpeed, SpaceshipRadius, SpaceshipMass, mTextureHolder.get(SpaceshipTextureName),
			SpaceshipMaxSpeed, SpaceshipBoost, SpaceshipBulletSpeed, SpaceshipBoostKey, SpaceshipAttackButton, SpaceshipSpecialAbilityKey, mTextureHolder.get(SpaceshipBulletTextureName));
	}

	void Game::run() {
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time timeSinceLastFrame = sf::Time::Zero;
		sf::Time timeSinceLastEnemySpawn = sf::seconds(9.f);

		while (mWindow.isOpen()){
			timeSinceLastUpdate = clock.restart();
			timeSinceLastFrame += timeSinceLastUpdate;
			timeSinceLastEnemySpawn += timeSinceLastUpdate;

			processInput();

			if (timeSinceLastEnemySpawn >= TimePerSpawn) {
				timeSinceLastEnemySpawn = sf::Time::Zero;
				nf::Enemy enemy;
				//������� ���������� �����
				enemy.setup(SpaceshipStartPosition, nf::Vector2f(rand()%200 - 100, rand()%200 - 100), SpaceshipRadius, SpaceshipMass, mTextureHolder.get(EnemyTextureName));
				mEnemies.push_back(enemy);
			}

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
		auto bulletIter = mSpaceship.getBullets().begin();
		auto enemyIter = mEnemies.begin();
		bool killed = false;
		while (enemyIter != mEnemies.end()) {
			bulletIter = mSpaceship.getBullets().begin();
			killed = false;
			while (bulletIter != mSpaceship.getBullets().end()) {
				if (enemyIter->isColliding(*bulletIter)) {
					enemyIter = mEnemies.erase(enemyIter);
					bulletIter = mSpaceship.getBullets().erase(bulletIter);
					killed = true;
					break;
				}
				else {
					++bulletIter;
				}
			}
			if (!killed) {
				++enemyIter;
			}
		}


		mSpaceship.update(deltaTime);
		for (int i = 0; i < mEnemies.size(); i++) {
			mEnemies[i].update(deltaTime);
		}
	}

	void Game::render() {
		mWindow.clear();
		
		for (int i = 0; i < mEnemies.size(); i++) {
			mWindow.draw(mEnemies[i].getSprite());
		}
		for (int i = 0; i < mSpaceship.getBullets().size(); i++) {
			mWindow.draw(mSpaceship.getBullets()[i].getSprite());
		}
		mWindow.draw(mSpaceship.getSprite());

		mWindow.display();
	}
}