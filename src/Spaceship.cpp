#include "Spaceship.hpp"

namespace nf {
	void Spaceship::setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius, const float mass,
		const sf::Texture* textureName, float maxSpeed, float boost, float bulletSpeed,
		const sf::Keyboard::Key& boostKey, const sf::Mouse::Button& attackButton, const sf::Keyboard::Key& specialAbilityKey, const sf::Texture* bulletTexture) {
		Object::setup(position, speed, radius, mass, textureName);
		mMaxSpeed = maxSpeed;
		mBoost = boost;
		mBulletSpeed = bulletSpeed;
		mBoostKey = boostKey;
		mAttackButton = attackButton;
		mSpecialAbilityKey = specialAbilityKey;
		mBulletTexture = bulletTexture;
	}

	void Spaceship::setMaxSpeed(const float maxSpeed) {
		mMaxSpeed = maxSpeed;
	}
	void Spaceship::setBoost(const float boost) {
		mBoost = boost;
	}
	void Spaceship::setBulletSpeed(const float bulletSpeed) {
		mBulletSpeed = bulletSpeed;
	}
	void Spaceship::setIsBoosting(const bool isBoosting) {
		mIsBoosting = isBoosting;
	}
	void Spaceship::setIsKilled(const bool isKilled) {
		mIsKilled = isKilled;
	}
	void Spaceship::setBoostKey(const sf::Keyboard::Key& boostKey) {
		mBoostKey = boostKey;
	}
	void Spaceship::setAttackButton(const sf::Mouse::Button& attackButton) {
		mAttackButton = attackButton;
	}
	void Spaceship::setSpecialAbilityKey(const sf::Keyboard::Key& specialAbilityKey) {
		mSpecialAbilityKey = specialAbilityKey;
	}

	const float Spaceship::getMaxSpeed() const {
		return mMaxSpeed;
	}
	const float Spaceship::getBoost() const {
		return mBoost;
	}
	const float Spaceship::getBulletSpeed() const {
		return mBulletSpeed;
	}
	const bool Spaceship::getIsBoosting() const {
		return mIsBoosting;
	}
	const bool Spaceship::getIsKilled() const {
		return mIsKilled;
	}
	const sf::Keyboard::Key& Spaceship::getBoostKey() const {
		return mBoostKey;
	}
	const sf::Mouse::Button& Spaceship::getAttackButton() const {
		return mAttackButton;
	}
	const sf::Keyboard::Key& Spaceship::getSpecialAbilityKey() const {
		return mSpecialAbilityKey;
	}
	std::vector<Object>& Spaceship::getBullets() {
		return mBullets;
	}

	void Spaceship::update(const sf::Time& deltaTime) {
		if (mIsBoosting && !mIsKilled) {
			boost(deltaTime);
		}

		if ((sf::Vector2f(sf::Mouse::getPosition()) - mPosition).y <= 0.f) {
			mSprite.setRotation(std::acos(nf::Vector2f(sf::Vector2f(sf::Mouse::getPosition()) - mPosition).normalized().x) * (-180.f / 3.14159f));
		}
		else {
			mSprite.setRotation(std::acos(nf::Vector2f(sf::Vector2f(sf::Mouse::getPosition()) - mPosition).normalized().x) * (180.f / 3.14159f));
		}

		if ((mPosition.x - mRadius < 0.f && mSpeed.x < 0.f) || (mPosition.x + mRadius > WindowWidth && mSpeed.x > 0.f)) {
			mSpeed.x *= -0.3f;
		}
		if ((mPosition.y - mRadius < 0.f && mSpeed.y < 0.f) || (mPosition.y + mRadius > WindowHeight && mSpeed.y > 0.f)) {
			mSpeed.y *= -0.3f;
		}

		Object::update(deltaTime);

		std::vector<Object>::iterator iter = mBullets.begin();
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

	void Spaceship::boost(const sf::Time& deltaTime) {
		mSpeed += nf::Vector2f(sf::Vector2f(sf::Mouse::getPosition()) - mPosition) * mBoost * deltaTime.asSeconds();
		if (std::abs(mSpeed.length()) > mMaxSpeed) {
			mSpeed = mSpeed.normalized() * mMaxSpeed;
		}
	}

	void Spaceship::shoot() {
		Object bullet;
		mBullets.push_back(bullet);

		mBullets.back().setup(mPosition, nf::Vector2f(sf::Vector2f(sf::Mouse::getPosition()) - mPosition).normalized() * mBulletSpeed,
			SpaceshipBulletRadius, SpaceshipBulletMass, mBulletTexture);
	}
}