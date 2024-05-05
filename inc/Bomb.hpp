#pragma once

#include "Enemy.hpp"

namespace nf {
	class Bomb : public Enemy {
	protected:
	public:
		void setup(nf::EnemyType type, const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
			const float mass, const sf::Texture* textureName, const float rotationSpeed);

		void specialAbility(nf::Game& game) override;
	};
}