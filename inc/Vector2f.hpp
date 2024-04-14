#pragma once

#include <SFML/System.hpp>

namespace nf {
	class Vector2f : public sf::Vector2f {
	public:
		Vector2f() : sf::Vector2f() {
		}
		Vector2f(float x, float y) : sf::Vector2f(x, y) {
		}
		Vector2f(sf::Vector2f& other) : sf::Vector2f(other) {
		}

		float length() const;
		void normalize();
		Vector2f normalized() const;
	};
}