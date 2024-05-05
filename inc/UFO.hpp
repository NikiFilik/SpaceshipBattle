#pragma once

#include "Enemy.hpp"

namespace nf {
	class UFO : public Enemy {
	protected:
		const sf::Texture* mBulletTexture;
		std::vector<nf::Enemy> mBullets;
	public:
		void setup(nf::EnemyType type, const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
			const float mass, const sf::Texture* textureName, const float rotationSpeed, const sf::Texture* bulletTexture);

		std::vector<Enemy>& getBullets() override;

		void update(const sf::Time& deltaTime) override;

		void specialAbility(nf::Game& game) override;
	};
}