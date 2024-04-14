#include "Object.hpp"

#include "functions.hpp"

namespace nf {
	void Object::setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius, const float mass, const std::string& textureName) {
		mPosition = position;
		mSpeed = speed;
		mRadius = radius;
		mMass = mass;
		mTexture.loadFromFile(textureName);
		mSprite.setTexture(mTexture);
		mSprite.setOrigin(mRadius, mRadius);
		mSprite.setPosition(mPosition);
	}

	void Object::setPosition(const nf::Vector2f& position){
		mPosition = position;
		mSprite.setPosition(mPosition);
	}
	void Object::setSpeed(const nf::Vector2f& speed) {
		mSpeed = speed;
	}
	void Object::setRadius(const float radius) {
		mRadius = radius;
	}
	void Object::setMass(const float mass) {
		mMass = mass;
	}
	void Object::setSprite(const sf::Sprite& sprite) {
		mSprite = sprite;
	}
	void Object::setTexture(const sf::Texture& texture) {
		mTexture = texture;
	}

	const nf::Vector2f& Object::getPosition() const {
		return mPosition;
	}
	const nf::Vector2f& Object::getSpeed() const {
		return mSpeed;
	}
	const float Object::getRadius() const {
		return mRadius;
	}
	const float Object::getMass() const {
		return mMass;
	}
	const sf::Sprite& Object::getSprite() const {
		return mSprite;
	}
	const sf::Texture& Object::getTexture() const {
		return mTexture;
	}

	void Object::update(const sf::Time& deltaTime) {
		mPosition += mSpeed * deltaTime.asSeconds();
		mSprite.setPosition(mPosition);
	}

	bool Object::isColliding(const Object& other) const {
		nf::Vector2f deltaPosition = mPosition - other.getPosition();
		if (std::pow(deltaPosition.x, 2.f) + std::pow(deltaPosition.y, 2.f) <= std::pow(mRadius + other.getRadius(), 2.f)) {
			nf::Vector2f deltaSpeed = mSpeed - other.getSpeed();
			if (deltaPosition.x * deltaSpeed.x + deltaPosition.y * deltaSpeed.y <= 0) {
				return true;
			}
		}
		return false;
	}
	void Object::resolveCollision(Object& other) {
		//https://www.vobarian.com/collisions/2dcollisions2.pdf

		nf::Vector2f unitNormalVector = nf::Vector2f(mPosition - other.getPosition()).normalized();
		nf::Vector2f unitTangentVector(-unitNormalVector.y, unitNormalVector.x);

		float thisNormalSpeed = nf::scalarMultiplication(unitNormalVector, mSpeed);
		float thisTangentSpeed = nf::scalarMultiplication(unitTangentVector, mSpeed);
		float otherNormalSpeed = nf::scalarMultiplication(unitNormalVector, other.getSpeed());
		float otherTangentSpeed = nf::scalarMultiplication(unitTangentVector, other.getSpeed());

		float newThisNormalSpeed, newOtherNormalSpeed;
		nf::resolveOneDimensionalCollision(mMass, other.getMass(), thisNormalSpeed, otherNormalSpeed, newThisNormalSpeed, newOtherNormalSpeed);

		mSpeed = unitNormalVector * newThisNormalSpeed + unitTangentVector * thisTangentSpeed;
		other.setSpeed(unitNormalVector * newOtherNormalSpeed + unitTangentVector * otherTangentSpeed);
	}
}