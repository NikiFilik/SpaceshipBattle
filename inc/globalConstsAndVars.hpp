#pragma once

#include <SFML/System.hpp>

namespace nf {
	const int WindowWidth = 1920, WindowHeight = 1080;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	const nf::Vector2f SpaceshipStartPosition(960.f, 540.f);
	const nf::Vector2f SpaceshipStartSpeed(0.f, 0.f);
	const float SpaceshipRadius = 48.f, SpaceshipMass = 1.f;
	const std::string SpaceshipTextureName = "media/textures/spaceship.png";
	const float SpaceshipMaxSpeed = 500.f, SpaceshipBoost = 1.f, SpaceshipBulletSpeed = 1500.f;
	const sf::Keyboard::Key SpaceshipBoostKey = sf::Keyboard::W, SpaceshipSpecialAbilityKey = sf::Keyboard::Space;
	const sf::Mouse::Button SpaceshipAttackButton = sf::Mouse::Left;
}