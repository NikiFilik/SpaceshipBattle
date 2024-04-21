#include "Enemy.hpp"

namespace nf {
	void Enemy::setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
		const float mass, const sf::Texture* textureName, const float rotationSpeed) {
		Object::setup(position, speed, radius, mass, textureName);
		mRotationSpeed = rotationSpeed;
	}

	const bool Enemy::getWasOnScreen() const {
		return mWasOnScreen;
	}

	void Enemy::update(const sf::Time& deltaTime) {
		mSprite.rotate(mRotationSpeed * deltaTime.asSeconds());
		if (mPosition.x + mRadius >= 0 && mPosition.x - mRadius <= WindowWidth 
			&& mPosition.y + mRadius >= 0 && mPosition.y - mRadius <= WindowHeight) {
			mWasOnScreen = true;
		}
		Object::update(deltaTime);
	}
}