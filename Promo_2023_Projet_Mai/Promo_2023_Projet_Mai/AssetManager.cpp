#include "AssetManager.h"
#include <fstream>

AssetManager::AssetManager()
{
	std::ifstream read("../Ressources/map/Assets_liste.txt");

	if (read.is_open()) {
		std::string line;

		while (std::getline(read, line)) {
			std::string name;
			sf::Vector2f pos;
			float reverse = 1;

			if (line.substr(line.size() - 1, line.size()) == "R") {
				reverse = -1;
			}

			name = line.substr(0, line.find(" : "));
			line.erase(0, line.find(" : ") + 3);

			pos.y = std::stof(line.substr(0, line.find(" ")));
			line.erase(0, line.find(" ") + 1);

			pos.x = std::stof(line.substr(0, line.find(" ")));
			line.erase(0, line.size());

			Assets.push_back(Asset(pos, name, reverse));
		}

		read.close();
	}
}

void AssetManager::AddInDrawable(Draw& drawable)
{
	for (auto& it : Assets) {
		drawable.push_back(std::make_pair(false, &it.GetSprite()));
	}
}

void AssetManager::Update(const float& dt)
{
	for (auto& it : Assets)
		it.Update(dt);
}

void AssetManager::Display(sf::RenderTexture& window)
{
	for (auto& it : Assets) {
		it.Display(window);
	}
}