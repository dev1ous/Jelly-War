#pragma once
#include "Bonus.h"
#include <list>

using Draw = std::list<std::pair<bool, sf::Sprite*>>;

class Network;

class ManagerBonus
{
private:
	std::list<Bonus> BonusMap;
	std::vector<sf::Vector2f> Pos;

public:
	ManagerBonus();
	~ManagerBonus() = default;

	std::list<Bonus>& GetBonusMap() { return BonusMap; }

	void AddBonus(sf::Vector2f pos, Bonus::Type type, Draw& drawale);
	void Apparition(Draw& drawale, Network* network);
	void Update(const float& dt);
};