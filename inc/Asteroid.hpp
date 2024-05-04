#pragma once

#include "Enemy.hpp"

namespace nf {
	class Asteroid : public Enemy {
	protected:
		const sf::Texture* mMiniTexture;
	public:
		void setup(nf::EnemyType type, const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
			const float mass, const sf::Texture* textureName, const float rotationSpeed, const sf::Texture* miniTexture);

		void specialAbility(nf::Game& game) override;
	};
}