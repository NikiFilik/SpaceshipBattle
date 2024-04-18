#include "TextureHolder.hpp"

namespace nf {
	void TextureHolder::load(const std::string& filename) {
		sf::Texture texture;
		texture.loadFromFile(filename);
		mTextureMap[filename] = texture;
	}
	const sf::Texture& TextureHolder::get(const std::string& filename) const {
		return mTextureMap.at(filename);
	}
}