#pragma once

#include "Vector2f.hpp"

namespace nf {
	float scalarMultiplication(const nf::Vector2f& a, const nf::Vector2f& b);

	void resolveOneDimensionalCollision(float mass1, float mass2, float speed1, float speed2, float& newSpeed1, float& newSpeed2);

	int randIntFromRange(const int a, const int b);
}