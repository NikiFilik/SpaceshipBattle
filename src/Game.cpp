#include "Game.hpp"

#include "globalConstsAndVars.hpp"
#include "functions.hpp"

#include <iostream>

namespace nf {
	void Asteroid::specialAbility(nf::Game& game) {
		nf::Enemy miniEnemy1, miniEnemy2, miniEnemy3;

		float distanceFromCentre = 2.f * MiniAsteroidRadius / std::sqrt(3.f);

		nf::Vector2f miniPosition1 = mPosition + nf::Vector2f(cos(distanceFromCentre * mSprite.getRotation() * (3.14159f / 180.f)), sin(distanceFromCentre * mSprite.getRotation() * (3.14159f / 180.f))),
			miniPosition2 = mPosition + nf::Vector2f(cos(distanceFromCentre * (mSprite.getRotation() + 120.f) * (3.14159f / 180.f)), sin(distanceFromCentre * (mSprite.getRotation() + 120.f) * (3.14159f / 180.f))),
			miniPosition3 = mPosition + nf::Vector2f(cos(distanceFromCentre * (mSprite.getRotation() - 120.f) * (3.14159f / 180.f)), sin(distanceFromCentre * (mSprite.getRotation() - 120.f) * (3.14159f / 180.f)));

		nf::Vector2f miniSpeed1 = mSpeed + nf::Vector2f(cos(distanceFromCentre * mSprite.getRotation() * (3.14159f / 180.f)), sin(distanceFromCentre * mSprite.getRotation() * (3.14159f / 180.f))) * 10.f,
			miniSpeed2 = mSpeed + nf::Vector2f(cos(distanceFromCentre * (mSprite.getRotation() + 120.f) * (3.14159f / 180.f)), sin(distanceFromCentre * (mSprite.getRotation() + 120.f) * (3.14159f / 180.f))) * 10.f,
			miniSpeed3 = mSpeed + nf::Vector2f(cos(distanceFromCentre * (mSprite.getRotation() - 120.f) * (3.14159f / 180.f)), sin(distanceFromCentre * (mSprite.getRotation() - 120.f) * (3.14159f / 180.f))) * 10.f;

		miniEnemy1.setup(miniPosition1, miniSpeed1, MiniAsteroidRadius, MiniAsteroidMass, mMiniTexture, nf::randIntFromRange(-60, 60));
		miniEnemy2.setup(miniPosition2, miniSpeed2, MiniAsteroidRadius, MiniAsteroidMass, mMiniTexture, nf::randIntFromRange(-60, 60));
		miniEnemy3.setup(miniPosition3, miniSpeed3, MiniAsteroidRadius, MiniAsteroidMass, mMiniTexture, nf::randIntFromRange(-60, 60));

		game.mEnemies.push_back(miniEnemy1);
		game.mEnemies.push_back(miniEnemy2);
		game.mEnemies.push_back(miniEnemy3);

		std::cout << "pipa";
	}

	Game::Game(): mWindow(sf::VideoMode(WindowWidth, WindowHeight), "Spaceship Battle", sf::Style::Fullscreen)
	{
		mWindow.setVerticalSyncEnabled(true);

		mTextureHolder.load(BackgroundTextureName);
		mTextureHolder.load(SpaceshipOnTextureName);
		mTextureHolder.load(SpaceshipOffTextureName);
		mTextureHolder.load(SpaceshipKilledTextureName);
		mTextureHolder.load(SpaceshipBulletTextureName);
		mTextureHolder.load(AsteroidTextureName);
		mTextureHolder.load(MiniAsteroidTextureName);

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
		}
	}
	void Game::processPlayerInput(const sf::Mouse::Button& button, const bool isPressed) {
		if (button == mSpaceship.getAttackButton() && isPressed && !mSpaceship.getIsKilled()) {
			mSpaceship.shoot();
		}
	}

	void Game::enemySpawn() {
		bool spawned = false;
		int attemptCounter = 0;
		while ((!spawned) && attemptCounter < 10) {
			nf::Asteroid asteroid;
			int spawnX, spawnY, side = nf::randIntFromRange(1, 4);
			if (side == 1) {
				spawnX = randIntFromRange(-AsteroidRadius, WindowWidth + AsteroidRadius);
				spawnY = -AsteroidRadius;
			}
			else if (side == 2) {
				spawnX = WindowWidth + AsteroidRadius;
				spawnY = randIntFromRange(-AsteroidRadius, WindowHeight + AsteroidRadius);
			}
			else if (side == 3) {
				spawnX = randIntFromRange(-AsteroidRadius, WindowWidth + AsteroidRadius);
				spawnY = WindowHeight + AsteroidRadius;
			}
			else if (side == 4) {
				spawnX = -AsteroidRadius;
				spawnY = randIntFromRange(-AsteroidRadius, WindowHeight + AsteroidRadius);
			}
			nf::Vector2f asteroidSpawn(spawnX, spawnY);
			nf::Vector2f asteroidSpeed(randIntFromRange(0, WindowWidth) - spawnX, randIntFromRange(0, WindowHeight) - spawnY);
			asteroidSpeed.normalize();
			asteroidSpeed *= float(randIntFromRange(AsteroidMinSpawnSpeed, AsteroidMaxSpawnSpeed));

			asteroid.setup(asteroidSpawn, asteroidSpeed, AsteroidRadius, AsteroidMass,
				mTextureHolder.get(AsteroidTextureName), nf::randIntFromRange(-60, 60), mTextureHolder.get(MiniAsteroidTextureName));

			bool isColliding = false;

			auto iter = mEnemies.begin();
			while (iter != mEnemies.end()) {
				if (asteroid.isColliding(*iter)) {
					isColliding = true;
					break;
				}
				iter++;
			}
			if (!isColliding) {
				mEnemies.push_back(asteroid);
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
					/*FFFFF*/
					enemyIter->specialAbility(*this);
					/*FFFFF*/
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
				mSpaceship.setIsKilled(true);
				mSpaceship.resolveCollision(mEnemies[i]);
			}
			for (int j = i + 1; j < mEnemies.size(); ++j) {
				if (mEnemies[i].isColliding(mEnemies[j])) {
					mEnemies[i].resolveCollision(mEnemies[j]);
				}
			}
		}

		if (mSpaceship.getIsKilled()) {
			mSpaceship.setTexture(mTextureHolder.get(SpaceshipKilledTextureName));
		}
		else {
			if (mSpaceship.getIsBoosting()) {
				mSpaceship.setTexture(mTextureHolder.get(SpaceshipOnTextureName));
			}
			else {
				mSpaceship.setTexture(mTextureHolder.get(SpaceshipOffTextureName));
			}
		}

		mSpaceship.update(deltaTime);

		std::vector<Enemy>::iterator iter = mEnemies.begin();
		while (iter != mEnemies.end()) {
			(*iter).update(deltaTime);
			if ((((*iter).getPosition().x + (*iter).getRadius() < 0.f || (*iter).getPosition().x - (*iter).getRadius() > WindowWidth ||
				(*iter).getPosition().y + (*iter).getRadius() < 0.f || (*iter).getPosition().y - (*iter).getRadius() > WindowHeight) && (*iter).getWasOnScreen()) || 
				((*iter).getPosition().x < 0.f - 500.f || (*iter).getPosition().x > WindowWidth + 500.f ||
					(*iter).getPosition().y < 0.f - 500.f || (*iter).getPosition().y > WindowHeight + 500.f)) {
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