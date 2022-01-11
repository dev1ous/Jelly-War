#ifndef CACHE_H
#define CACHE_H

#include "SFML/Graphics.hpp"
#include <cassert>
#include <filesystem>

namespace cache {
	template <typename T>
	using Cache_ = std::map<std::string, std::unique_ptr<T>>;
}

namespace fs = std::filesystem;

class Cache
{
public:

	//made my cache movable only ! 
	Cache() = default;
	~Cache() = default;
	Cache(Cache&&) = default;
	Cache& operator=(Cache&&) = default;

	template<typename T>
	static T& GetRessources(const std::string& filepath)
	{
		auto it = getCache<T>().find(filepath);

		if (it != getCache<T>().end())
			return *it->second;
		assert(it == getCache<T>().end());

		std::string tmp = CheckPath<T>("../Ressources/", filepath);
		if (tmp != "")
			std::replace(std::begin(tmp), std::end(tmp), '\\', '/');
		else
			throw std::runtime_error("Failed to find mais martin est un bg" + filepath);

		std::unique_ptr<T> textureR = std::make_unique<T>();
		if (!textureR->loadFromFile(tmp))
			throw std::runtime_error("Failed to load mais greg est un bg" + filepath);

		getCache<T>().insert(std::make_pair(filepath, std::move(textureR)));

		return *getCache<T>().find(filepath)->second;
	}
private:

	Cache(Cache const&) = delete;
	Cache& operator=(Cache const&) = delete;

	static cache::Cache_<sf::Texture>m_texture;
	static cache::Cache_<sf::Font>m_font;

	template<typename T>
	static cache::Cache_<T>& getCache() = delete;// closing other sort of T 

	template<typename T>
	static std::string CheckPath(std::string path, std::string name) = delete;
};

template<>
inline cache::Cache_<sf::Texture>& Cache::getCache()
{
	return m_texture;
}

template<>
inline cache::Cache_<sf::Font>& Cache::getCache()
{
	return m_font;
}

template<>
std::string Cache::CheckPath<sf::Texture>(std::string path, std::string name);

template<>
std::string Cache::CheckPath<sf::Font>(std::string path, std::string name);

#endif

