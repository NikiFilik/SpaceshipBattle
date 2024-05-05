#include "Bomb.hpp"

#include "globalConstsAndVars.hpp"
#include "functions.hpp"

namespace nf {
	void Bomb::setup(nf::EnemyType type, const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
		const float mass, const sf::Texture* textureName, const float rotationSpeed) {
		Enemy::setup(type, position, speed, radius, mass, textureName, rotationSpeed);
	}
}