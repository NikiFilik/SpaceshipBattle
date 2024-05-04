#pragma once

#include "Object.hpp"
#include <iostream>

namespace nf {
	class Game;

	class Enemy : public Object {
	protected:
		bool mWasOnScreen = false;
		float mRotationSpeed;
	public:
		void setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
			const float mass, const sf::Texture* textureName, const float rotationSpeed);

		const bool getWasOnScreen() const;

		virtual void update(const sf::Time& deltaTime) override;

		virtual void specialAbility(nf::Game& game);

		virtual void setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
			const float mass, const sf::Texture* textureName, const float rotationSpeed, const sf::Texture* miniTexture) {
			std::cout << "NE TOT SETUP\n";
		}
	};
}