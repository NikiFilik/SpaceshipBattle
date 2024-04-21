#include "Game.hpp"

#include "globalConstsAndVars.hpp"
#include "functions.hpp"

namespace nf {
	Game::Game(): mWindow(sf::VideoMode(WindowWidth, WindowHeight), "Spaceship Battle", sf::Style::Fullscreen)
	{
		mWindow.setVerticalSyncEnabled(true);

		mTextureHolder.load(BackgroundTextureName);
		mTextureHolder.load(SpaceshipOnTextureName);
		mTextureHolder.load(SpaceshipOffTextureName);
		mTextureHolder.load(SpaceshipBulletTextureName);
		mTextureHolder.load(EnemyTextureName);

		mBackground.setTexture(*mTextureHolder.get(BackgroundTextureName));

		mSpaceship.setup(SpaceshipStartPosition, SpaceshipStartSpeed, SpaceshipRadius, SpaceshipMass, mTextureHolder.get(SpaceshipOffTextureName),
			SpaceshipMaxSpeed, SpaceshipBoost, SpaceshipBulletSpeed, SpaceshipBoostKey, SpaceshipAttackButton, SpaceshipSpecialAbilityKey, mTextureHolder.get(SpaceshipBulletTextureName));
	}

	void Game::run() {
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time timeSinceLastFrame = sf::Time::Zero;
		sf::Time timeSinceLastEnemySpawn = sf::Time::Zero;

		while (mWindow.isOpen()){
			timeSinceLastUpdate = clock.restart();
			timeSinceLastFrame += timeSinceLastUpdate;
			timeSinceLastEnemySpawn += timeSinceLastUpdate;

			processInput();

			if (timeSinceLastEnemySpawn >= TimePerSpawn) {
				timeSinceLastEnemySpawn = sf::Time::Zero;
				enemySpawn();
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
			if (isPressed) {
				mSpaceship.setTexture(mTextureHolder.get(SpaceshipOnTextureName));
			}
			else {
				mSpaceship.setTexture(mTextureHolder.get(SpaceshipOffTextureName));
			}
		}
	}
	void Game::processPlayerInput(const sf::Mouse::Button& button, const bool isPressed) {
		if (button == mSpaceship.getAttackButton() && isPressed) {
			mSpaceship.shoot();
		}
	}

	void Game::enemySpawn() {
		bool spawned = false;
		int attemptCounter = 0;
		while (!spawned && attemptCounter < 10) {
			nf::Enemy enemy;
			int spawnX, spawnY, side = nf::randIntFromRange(1, 4);
			if (side == 1) {
				spawnX = randIntFromRange(-EnemyRadius, WindowWidth + EnemyRadius);
				spawnY = -EnemyRadius;
			}
			else if (side == 2) {
				spawnX = WindowWidth + EnemyRadius;
				spawnY = randIntFromRange(-EnemyRadius, WindowHeight + EnemyRadius);
			}
			else if (side == 3) {
				spawnX = randIntFromRange(-EnemyRadius, WindowWidth + EnemyRadius);
				spawnY = WindowHeight + EnemyRadius;
			}
			else if (side == 4) {
				spawnX = -EnemyRadius;
				spawnY = randIntFromRange(-EnemyRadius, WindowHeight + EnemyRadius);
			}
			nf::Vector2f enemySpawn(spawnX, spawnY);
			nf::Vector2f enemySpeed(randIntFromRange(0, WindowWidth) - spawnX, randIntFromRange(0, WindowHeight) - spawnY);
			enemySpeed.normalize();
			enemySpeed *= float(randIntFromRange(EnemyMinSpawnSpeed, EnemyMaxSpawnSpeed));

			enemy.setup(enemySpawn, enemySpeed, EnemyRadius, EnemyMass, 
				mTextureHolder.get(EnemyTextureName), nf::randIntFromRange(-60, 60));

			bool isColliding = false;

			auto iter = mEnemies.begin();
			while (iter != mEnemies.end()) {
				if (enemy.isColliding(*iter)) {
					isColliding = true;
					break;
				}
				iter++;
			}
			if (!isColliding) {
				mEnemies.push_back(enemy);
				spawned = true;
			}
			++attemptCounter;
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

		for (int i = 0; i < mEnemies.size(); ++i) {
			if (mSpaceship.isColliding(mEnemies[i])) {
				mSpaceship.resolveCollision(mEnemies[i]);
			}
			for (int j = i + 1; j < mEnemies.size(); ++j) {
				if (mEnemies[i].isColliding(mEnemies[j])) {
					mEnemies[i].resolveCollision(mEnemies[j]);
				}
			}
		}

		mSpaceship.update(deltaTime);
		std::vector<Enemy>::iterator iter = mEnemies.begin();
		while (iter != mEnemies.end()) {
			(*iter).update(deltaTime);
			if (((*iter).getPosition().x + (*iter).getRadius() < 0.f || (*iter).getPosition().x - (*iter).getRadius() > WindowWidth ||
				(*iter).getPosition().y + (*iter).getRadius() < 0.f || (*iter).getPosition().y - (*iter).getRadius() > WindowHeight) && (*iter).getWasOnScreen()) {
				iter = mEnemies.erase(iter);
			}
			else {
				++iter;
			}
		}
	}

	void Game::render() {
		mWindow.clear();
		
		mWindow.draw(mBackground);
		for (int i = 0; i < mEnemies.size(); ++i) {
			mWindow.draw(mEnemies[i].getSprite());
		}
		for (int i = 0; i < mSpaceship.getBullets().size(); ++i) {
			mWindow.draw(mSpaceship.getBullets()[i].getSprite());
		}
		mWindow.draw(mSpaceship.getSprite());

		mWindow.display();
	}
}