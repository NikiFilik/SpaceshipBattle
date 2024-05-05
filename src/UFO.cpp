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

	void UFO::update(const sf::Time& deltaTime) {
		Enemy::update(deltaTime);

		auto iter = mBullets.begin();
		while (iter != mBullets.end()) {
			(*iter).update(deltaTime);
			if ((*iter).getPosition().x + (*iter).getRadius() < 0.f || (*iter).getPosition().x - (*iter).getRadius() > WindowWidth ||
				(*iter).getPosition().y + (*iter).getRadius() < 0.f || (*iter).getPosition().y - (*iter).getRadius() > WindowHeight) {
				iter = mBullets.erase(iter);
			}
			else {
				++iter;
			}
		}
	}
}