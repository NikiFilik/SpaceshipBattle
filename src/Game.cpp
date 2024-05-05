#include "Game.hpp"

#include "globalConstsAndVars.hpp"
#include "functions.hpp"

namespace nf {
	void Asteroid::specialAbility(nf::Game& game) {
		std::shared_ptr<nf::Enemy> miniEnemy1 = std::make_shared<nf::Enemy>();
		std::shared_ptr<nf::Enemy> miniEnemy2 = std::make_shared<nf::Enemy>();
		std::shared_ptr<nf::Enemy> miniEnemy3 = std::make_shared<nf::Enemy>();

		float distanceFromCentre = 2.f * MiniAsteroidRadius / std::sqrt(3.f);

		nf::Vector2f miniPosition1 = mPosition + nf::Vector2f(distanceFromCentre * cos(mSprite.getRotation() * (3.14159f / 180.f)), distanceFromCentre * sin(mSprite.getRotation() * (3.14159f / 180.f))),
			miniPosition2 = mPosition + nf::Vector2f(distanceFromCentre * cos((mSprite.getRotation() + 120.f) * (3.14159f / 180.f)), distanceFromCentre * sin((mSprite.getRotation() + 120.f) * (3.14159f / 180.f))),
			miniPosition3 = mPosition + nf::Vector2f(distanceFromCentre * cos((mSprite.getRotation() - 120.f) * (3.14159f / 180.f)), distanceFromCentre * sin((mSprite.getRotation() - 120.f) * (3.14159f / 180.f)));

		nf::Vector2f miniSpeed1 = mSpeed + nf::Vector2f(cos(mSprite.getRotation() * (3.14159f / 180.f)), sin(mSprite.getRotation() * (3.14159f / 180.f))) * 150.f,
			miniSpeed2 = mSpeed + nf::Vector2f(cos((mSprite.getRotation() + 120.f) * (3.14159f / 180.f)), sin((mSprite.getRotation() + 120.f) * (3.14159f / 180.f))) * 150.f,
			miniSpeed3 = mSpeed + nf::Vector2f(cos((mSprite.getRotation() - 120.f) * (3.14159f / 180.f)), sin((mSprite.getRotation() - 120.f) * (3.14159f / 180.f))) * 150.f;

		miniEnemy1->setup(nf::EnemyType::Base, miniPosition1, miniSpeed1, MiniAsteroidRadius, MiniAsteroidMass, mMiniTexture, nf::randIntFromRange(-60, 60));
		miniEnemy2->setup(nf::EnemyType::Base, miniPosition2, miniSpeed2, MiniAsteroidRadius, MiniAsteroidMass, mMiniTexture, nf::randIntFromRange(-60, 60));
		miniEnemy3->setup(nf::EnemyType::Base, miniPosition3, miniSpeed3, MiniAsteroidRadius, MiniAsteroidMass, mMiniTexture, nf::randIntFromRange(-60, 60));

		game.mEnemies.push_back(miniEnemy1);
		game.mEnemies.push_back(miniEnemy2);
		game.mEnemies.push_back(miniEnemy3);
	}

	void UFO::specialAbility(nf::Game& game) {
		float A, B, C, D, t1, t2;
		A = std::pow(game.mSpaceship.getSpeed().x, 2) + std::pow(game.mSpaceship.getSpeed().y, 2) - pow(UFOBulletSpeed, 2);
		B = 2.f * (game.mSpaceship.getSpeed().x * (game.mSpaceship.getPosition().x - mPosition.x) + game.mSpaceship.getSpeed().y * (game.mSpaceship.getPosition().y - mPosition.y));
		C = std::pow(game.mSpaceship.getPosition().x, 2) + std::pow(mPosition.x, 2) - 2.f * game.mSpaceship.getPosition().x * mPosition.x + 
			std::pow(game.mSpaceship.getPosition().y, 2) + std::pow(mPosition.y, 2) - 2.f * game.mSpaceship.getPosition().y * mPosition.y;

		D = B * B - 4.f * A * C;
		
		if (D >= 0) {
			t1 = (-B + std::sqrt(D)) / (2 * A);
			t2 = (-B - std::sqrt(D)) / (2 * A);
			float t = std::max(t1, t2);
			if (t > 0) {
				nf::Vector2f target(game.mSpaceship.getPosition() + game.mSpaceship.getSpeed() * t);
				nf::Vector2f bulletSpeed((nf::Vector2f(target - mPosition)).normalized() * UFOBulletSpeed);

				nf::Enemy bullet;
				bullet.setup(nf::EnemyType::Base, mPosition, bulletSpeed, UFOBulletRadius, UFOBulletMass, mBulletTexture, 0.f);
				mBullets.push_back(bullet);
			}
		}
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
		mTextureHolder.load(UFOTextureName);
		mTextureHolder.load(UFOBulletTextureName);

		mBackground.setTexture(*mTextureHolder.get(BackgroundTextureName));

		mSpaceship.setup(SpaceshipStartPosition, SpaceshipStartSpeed, SpaceshipRadius, SpaceshipMass, mTextureHolder.get(SpaceshipOffTextureName),
			SpaceshipMaxSpeed, SpaceshipBoost, SpaceshipBulletSpeed, SpaceshipBoostKey, SpaceshipAttackButton, SpaceshipSpecialAbilityKey, mTextureHolder.get(SpaceshipBulletTextureName));
	}

	void Game::run() {
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time timeSinceLastFrame = sf::Time::Zero;
		sf::Time timeSinceLastEnemySpawn = sf::Time::Zero;
		sf::Time timeSinceLastAttack = sf::Time::Zero;

		while (mWindow.isOpen()){
			timeSinceLastUpdate = clock.restart();
			timeSinceLastFrame += timeSinceLastUpdate;
			timeSinceLastEnemySpawn += timeSinceLastUpdate;
			timeSinceLastAttack += timeSinceLastUpdate;

			processInput();

			if (timeSinceLastEnemySpawn >= TimePerSpawn) {
				timeSinceLastEnemySpawn = sf::Time::Zero;
				enemySpawn();
			}

			if (timeSinceLastAttack >= TimePerAttack) {
				timeSinceLastAttack = sf::Time::Zero;
				enemyAttack();
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
		int type = nf::randIntFromRange(1, 2);
		if (type == 1) {
			bool spawned = false;
			int attemptCounter = 0;
			while ((!spawned) && attemptCounter < 10) {
				std::shared_ptr<nf::Enemy> asteroid = std::make_shared<nf::Asteroid>();
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

				asteroid->setup(nf::EnemyType::Asteroid, asteroidSpawn, asteroidSpeed, AsteroidRadius, AsteroidMass,
					mTextureHolder.get(AsteroidTextureName), nf::randIntFromRange(-60, 60), mTextureHolder.get(MiniAsteroidTextureName));

				bool isColliding = false;

				auto iter = mEnemies.begin();
				while (iter != mEnemies.end()) {
					if (asteroid->isColliding(*(*iter))) {
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
		else if (type == 2) {
			bool spawned = false;
			int attemptCounter = 0;
			while ((!spawned) && attemptCounter < 10) {
				std::shared_ptr<nf::Enemy> ufo = std::make_shared<nf::UFO>();
				int spawnX, spawnY, side = nf::randIntFromRange(1, 4);
				if (side == 1) {
					spawnX = randIntFromRange(-UFORadius, WindowWidth + UFORadius);
					spawnY = -UFORadius;
				}
				else if (side == 2) {
					spawnX = WindowWidth + UFORadius;
					spawnY = randIntFromRange(-UFORadius, WindowHeight + UFORadius);
				}
				else if (side == 3) {
					spawnX = randIntFromRange(-UFORadius, WindowWidth + UFORadius);
					spawnY = WindowHeight + UFORadius;
				}
				else if (side == 4) {
					spawnX = -UFORadius;
					spawnY = randIntFromRange(-UFORadius, WindowHeight + UFORadius);
				}
				nf::Vector2f ufoSpawn(spawnX, spawnY);
				nf::Vector2f ufoSpeed(randIntFromRange(0, WindowWidth) - spawnX, randIntFromRange(0, WindowHeight) - spawnY);
				ufoSpeed.normalize();
				ufoSpeed *= float(randIntFromRange(UFOMinSpawnSpeed, UFOMaxSpawnSpeed));

				ufo->setup(nf::EnemyType::UFO, ufoSpawn, ufoSpeed, UFORadius, UFOMass,
					mTextureHolder.get(UFOTextureName), nf::randIntFromRange(-60, 60), mTextureHolder.get(UFOBulletTextureName));

				bool isColliding = false;

				auto iter = mEnemies.begin();
				while (iter != mEnemies.end()) {
					if (ufo->isColliding(*(*iter))) {
						isColliding = true;
						break;
					}
					iter++;
				}
				if (!isColliding) {
					mEnemies.push_back(ufo);
					spawned = true;
				}
				++attemptCounter;
			}
		}
	}

	void Game::enemyAttack() {
		auto iter = mEnemies.begin();
		while (iter != mEnemies.end()) {
			if ((*iter)->getEnemyType() == nf::EnemyType::UFO) {
				(*iter)->specialAbility(*this);
			}
			++iter;
		}
	}

	void Game::update(const sf::Time& deltaTime) {
		int bInd = 0;
		bool killed = false;
		for (int eInd = 0; eInd < mEnemies.size();) {
			bInd = 0;
			killed = false;
			for (bInd = 0; bInd < mSpaceship.getBullets().size();) {
				if ((mEnemies[eInd])->isColliding(mSpaceship.getBullets()[bInd])) {

					if (mEnemies[eInd]->getEnemyType() == nf::EnemyType::Asteroid) {
						mEnemies[eInd]->specialAbility(*this);
					}

					auto iter = mEnemies.begin() + eInd;
					iter = mEnemies.erase(iter);
					auto iter2 = mSpaceship.getBullets().begin() + bInd;
					iter2 = mSpaceship.getBullets().erase(iter2);
					killed = true;
					break;
				}
				else {
					++bInd;
				}
			}
			if (!killed) {
				++eInd;
			}
		}

		for (int i = 0; i < mEnemies.size(); ++i) {
			if (mSpaceship.isColliding(*(mEnemies[i]))) {
				mSpaceship.setIsKilled(true);
				mSpaceship.resolveCollision(*(mEnemies[i]));
			}
			for (int j = i + 1; j < mEnemies.size(); ++j) {
				if (mEnemies[i]->isColliding(*(mEnemies[j]))) {
					mEnemies[i]->resolveCollision(*(mEnemies[j]));
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

		auto iter = mEnemies.begin();
		while (iter != mEnemies.end()) {
			(*iter)->update(deltaTime);

			if ((*iter)->getEnemyType() == nf::EnemyType::UFO) {
				auto UFOBulletIter = (*iter)->getBullets().begin();
				while (UFOBulletIter != (*iter)->getBullets().end()) {
					if (UFOBulletIter->isColliding(mSpaceship)) {
						mSpaceship.setIsKilled(true);
						UFOBulletIter = (*iter)->getBullets().erase(UFOBulletIter);
					}
					else {
						UFOBulletIter++;
					}
				}
			}

			if ((((*iter)->getPosition().x + (*iter)->getRadius() < 0.f || (*iter)->getPosition().x - (*iter)->getRadius() > WindowWidth ||
				(*iter)->getPosition().y + (*iter)->getRadius() < 0.f || (*iter)->getPosition().y - (*iter)->getRadius() > WindowHeight) && (*iter)->getWasOnScreen()) || 
				((*iter)->getPosition().x < 0.f - 500.f || (*iter)->getPosition().x > WindowWidth + 500.f ||
					(*iter)->getPosition().y < 0.f - 500.f || (*iter)->getPosition().y > WindowHeight + 500.f)) {
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
			mWindow.draw(mEnemies[i]->getSprite());
			if (mEnemies[i]->getEnemyType() == nf::EnemyType::UFO) {
				for (int j = 0; j < mEnemies[i]->getBullets().size(); ++j) {
					mWindow.draw(((mEnemies[i]->getBullets())[j]).getSprite());
				}
			}
		}

		for (int i = 0; i < mSpaceship.getBullets().size(); ++i) {
			mWindow.draw(mSpaceship.getBullets()[i].getSprite());
		}

		mWindow.draw(mSpaceship.getSprite());

		mWindow.display();
	}

	
}