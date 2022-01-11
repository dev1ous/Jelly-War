#pragma once
#include "Asset.h"
#include <list>

using Draw = std::list<std::pair<bool, sf::Sprite*>>;

class AssetManager
{
private:
	std::vector<Asset> Assets;

public:
	AssetManager();
	~AssetManager() = default;

	void AddInDrawable(Draw& drawable);

	void Update(const float& dt);
	void Display(sf::RenderTexture& window);
};