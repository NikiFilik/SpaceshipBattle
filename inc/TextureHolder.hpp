#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace nf {
	class TextureHolder {
	private:
		std::map<std::string, sf::Texture> mTextureMap;
	public:
		void load(const std::string& filename);
		const sf::Texture* get(const std::string& filename) const;
	};
}