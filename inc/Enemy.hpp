#pragma once

#include "Object.hpp"
#include <iostream>

namespace nf {
	class Game;

	class Enemy : public Object {
	protected:
		nf::EnemyType mType;
		bool mWasOnScreen = false;
		float mRotationSpeed;
	public:
		void setup(nf::EnemyType type, const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
			const float mass, const sf::Texture* textureName, const float rotationSpeed);

		nf::EnemyType getEnemyType() const;
		const bool getWasOnScreen() const;

		virtual void update(const sf::Time& deltaTime) override;

		virtual void specialAbility(nf::Game& game);
		virtual std::vector<nf::Enemy>& getBullets() {
			return std::vector<nf::Enemy>();
		}

		virtual void setup(nf::EnemyType type, const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
			const float mass, const sf::Texture* textureName, const float rotationSpeed, const sf::Texture* miniTexture) {
			std::cout << "NE TOT SETUP\n";
		}
	};
}