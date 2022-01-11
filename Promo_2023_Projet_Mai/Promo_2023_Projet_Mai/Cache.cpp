#include "Cache.h"

cache::Cache_<sf::Texture>Cache::m_texture;
cache::Cache_<sf::Font>Cache::m_font;

template<>
std::string Cache::CheckPath<sf::Texture>(std::string path, std::string name)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (entry.path().extension() == "")
		{
			if (CheckPath<sf::Texture>(entry.path().string(), name) != "")
				return CheckPath<sf::Texture>(entry.path().string(), name);
		}

		if (entry.path().stem() == name)
		{
			if (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")
				return entry.path().string();
		}
	}

	return "";
}

template<>
std::string Cache::CheckPath<sf::Font>(std::string path, std::string name)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (entry.path().extension() == "")
		{
			if (CheckPath<sf::Font>(entry.path().string(), name) != "")
				return CheckPath<sf::Font>(entry.path().string(), name);
		}

		if (entry.path().stem() == name)
		{
			if (entry.path().extension() == ".ttf" || entry.path().extension() == ".otf")
				return entry.path().string();
		}
	}

	return "";
}


