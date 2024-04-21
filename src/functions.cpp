#include "functions.hpp"

namespace nf {
	float scalarMultiplication(const nf::Vector2f& a, const nf::Vector2f& b) {
		return (a.x * b.x) + (a.y * b.y);
	}

	void resolveOneDimensionalCollision(float mass1, float mass2, float speed1, float speed2, float& newSpeed1, float& newSpeed2) {
		newSpeed1 = (speed1 * (mass1 - mass2) + 2 * mass2 * speed2) / (mass1 + mass2);
		newSpeed2 = (speed2 * (mass2 - mass1) + 2 * mass1 * speed1) / (mass1 + mass2);
	}

	int randIntFromRange(const int a, const int b) {
		return rand() % (b - a + 1) + a;
	}
}