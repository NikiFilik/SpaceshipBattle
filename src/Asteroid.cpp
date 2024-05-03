#include "Asteroid.hpp"

#include "globalConstsAndVars.hpp"
#include "functions.hpp"

namespace nf {
	void Asteroid::setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
		const float mass, const sf::Texture* textureName, const float rotationSpeed, const sf::Texture* miniTexture) {
		Enemy::setup(position, speed, radius, mass, textureName, rotationSpeed);
		mMiniTexture = miniTexture;
	}
}