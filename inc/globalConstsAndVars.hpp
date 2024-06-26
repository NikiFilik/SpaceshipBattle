#pragma once

#include <SFML/Graphics.hpp>
#include "Vector2f.hpp"

namespace nf {
	const int WindowWidth = 1920, WindowHeight = 1080;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f), TimePerSpawn = sf::seconds(1.f), TimePerAttack = sf::seconds(1.5f);
	const std::string BackgroundTextureName = "media/textures/background.png";
	const std::string FontFilename = "media/fonts/PIXY.ttf";

	const nf::Vector2f SpaceshipStartPosition(960.f, 540.f);
	const nf::Vector2f SpaceshipStartSpeed(0.f, 0.f);
	const float SpaceshipRadius = 48.f, SpaceshipMass = 2.f;
	const std::string SpaceshipOnTextureName = "media/textures/spaceshipOn.png", 
		SpaceshipOffTextureName = "media/textures/spaceshipOff.png", 
		SpaceshipKilledTextureName = "media/textures/spaceshipKilled.png", 
		SpaceshipBulletTextureName = "media/textures/bullet.png";
	const float SpaceshipMaxSpeed = 500.f, SpaceshipBoost = 1.f, SpaceshipBulletSpeed = 1000.f;
	const sf::Keyboard::Key SpaceshipBoostKey = sf::Keyboard::W, SpaceshipSpecialAbilityKey = sf::Keyboard::Space;
	const sf::Mouse::Button SpaceshipAttackButton = sf::Mouse::Left;
	const float SpaceshipBulletRadius = 12.f, SpaceshipBulletMass = 1.f;

	const std::string AsteroidTextureName = "media/textures/asteroid.png", MiniAsteroidTextureName = "media/textures/miniAsteroid.png";
	const float AsteroidRadius = 64.f, AsteroidMass = 3.f, MiniAsteroidRadius = 28.f, MiniAsteroidMass = 1.f;
	const float AsteroidMinSpawnSpeed = 150.f, AsteroidMaxSpawnSpeed = 250.f;

	const std::string UFOTextureName = "media/textures/ufo.png", UFOBulletTextureName = "media/textures/ufoBullet.png";
	const float UFORadius = 64.f, UFOMass = 6.f, UFOBulletSpeed = 700.f, UFOBulletRadius = 12.f, UFOBulletMass = 1.f;
	const float UFOMinSpawnSpeed = 150.f, UFOMaxSpawnSpeed = 250.f;

	const std::string BombTextureName = "media/textures/bomb.png";
	const float BombRadius = 48.f, BombMass = 2.f;
	const float BombMinSpawnSpeed = 150.f, BombMaxSpawnSpeed = 250.f;
	const float BombPower = 500000.f;

	enum class EnemyType {Base, Asteroid, UFO, Bomb};
}