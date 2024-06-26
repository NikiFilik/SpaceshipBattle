#pragma once

#include "Object.hpp"

namespace nf {
	class Spaceship : public Object {
	protected:
		float mMaxSpeed, mBoost, mBulletSpeed;
		bool mIsBoosting = false;
		sf::Keyboard::Key mBoostKey, mSpecialAbilityKey;
		sf::Mouse::Button mAttackButton;
		std::vector<Object> mBullets;
		const sf::Texture* mBulletTexture;
		bool mIsKilled = false;
	public:
		void setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius, const float mass, 
			const sf::Texture* textureName, float maxSpeed, float boost, float bulletSpeed, 
			const sf::Keyboard::Key& boostKey, const sf::Mouse::Button& attackButton, const sf::Keyboard::Key& specialAbilityKey, const sf::Texture* bulletTexture);

		void setMaxSpeed(const float maxSpeed);
		void setBoost(const float boost);
		void setBulletSpeed(const float bulletSpeed);
		void setIsBoosting(const bool isBoosting);
		void setIsKilled(const bool isKilled);
		void setBoostKey(const sf::Keyboard::Key& boostKey);
		void setAttackButton(const sf::Mouse::Button& attackButton);
		void setSpecialAbilityKey(const sf::Keyboard::Key& specialAbilityKey);

		const float getMaxSpeed() const;
		const float getBoost() const;
		const float getBulletSpeed() const;
		const bool getIsBoosting() const;
		const bool getIsKilled() const;
		const sf::Keyboard::Key& getBoostKey() const;
		virtual const sf::Mouse::Button& getAttackButton() const;
		virtual const sf::Keyboard::Key& getSpecialAbilityKey() const;
		std::vector<Object>& getBullets();

		void update(const sf::Time& deltaTime) override;

		void boost(const sf::Time& deltaTime);

		void shoot();
	};
}