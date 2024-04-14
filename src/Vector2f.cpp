#include "Vector2f.hpp"

namespace nf {
	float Vector2f::length() const {
		return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
	}
	void Vector2f::normalize() {
		x /= length();
		y /= length();
	}
	Vector2f Vector2f::normalized() const {
		return Vector2f(x / length(), y / length());
	}
}