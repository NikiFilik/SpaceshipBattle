#pragma once

#include <SFML/Graphics.hpp>
#include "Vector2f.hpp"

namespace nf {
	const int WindowWidth = 1920, WindowHeight = 1080;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f), TimePerSpawn = sf::seconds(1.f);
	const std::string BackgroundTextureName = "media/textures/background.png";

	const nf::Vector2f SpaceshipStartPosition(960.f, 540.f);
	const nf::Vector2f SpaceshipStartSpeed(0.f, 0.f);
	const float SpaceshipRadius = 48.f, SpaceshipMass = 1.f;
	const std::string SpaceshipOnTextureName = "media/textures/spaceshipOn.png", SpaceshipOffTextureName = "media/textures/spaceshipOff.png", SpaceshipBulletTextureName = "media/textures/bullet.png";
	const float SpaceshipMaxSpeed = 500.f, SpaceshipBoost = 1.f, SpaceshipBulletSpeed = 1000.f;
	const sf::Keyboard::Key SpaceshipBoostKey = sf::Keyboard::W, SpaceshipSpecialAbilityKey = sf::Keyboard::Space;
	const sf::Mouse::Button SpaceshipAttackButton = sf::Mouse::Left;
	const float SpaceshipBulletRadius = 12.f, SpaceshipBulletMass = 1.f;

	const std::string EnemyTextureName = "media/textures/enemy.png";
	const float EnemyRadius = 64.f, EnemyMass = 2.f;
	const float EnemyMinSpawnSpeed = 100.f, EnemyMaxSpawnSpeed = 200.f;
}