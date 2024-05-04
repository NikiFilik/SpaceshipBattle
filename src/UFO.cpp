#include "UFO.hpp"

#include "globalConstsAndVars.hpp"
#include "functions.hpp"

namespace nf {
	void UFO::setup(nf::EnemyType type, const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
		const float mass, const sf::Texture* textureName, const float rotationSpeed, const sf::Texture* bulletTexture) {
		Enemy::setup(type, position, speed, radius, mass, textureName, rotationSpeed);
		mBulletTexture = bulletTexture;
	}

	std::vector<Enemy>& UFO::getBullets() {
		return mBullets;
	}
}