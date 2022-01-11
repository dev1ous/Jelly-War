#include "ManagerBonus.h"
#include "Functions.h"
#include "Cache.h"
#include "Network.h"

ManagerBonus::ManagerBonus()
{
	Pos.push_back(sf::Vector2f(2360, 1080));
	Pos.push_back(sf::Vector2f(4000, 2117));
	Pos.push_back(sf::Vector2f(973, 3000));

	Pos.push_back(sf::Vector2f(2500, 4500));
	Pos.push_back(sf::Vector2f(2387, 4873));
	Pos.push_back(sf::Vector2f(1162, 7027));

	Pos.push_back(sf::Vector2f(3855, 6153));
	Pos.push_back(sf::Vector2f(6027, 6991));
	Pos.push_back(sf::Vector2f(6774, 4873));

	Pos.push_back(sf::Vector2f(4783, 2810));
	Pos.push_back(sf::Vector2f(7414, 3422));
	Pos.push_back(sf::Vector2f(7099, 6873));
}

void ManagerBonus::Update(const float& dt)
{
	for (auto& it : BonusMap)
		it.Anim.Animation(it.SpriteMap, dt);
}

void ManagerBonus::AddBonus(sf::Vector2f pos, Bonus::Type type, Draw& drawale)
{
	if (type != Bonus::Type::None) {
		for (auto it = BonusMap.begin(); it != BonusMap.end(); it++) {
			if (Collisions::Between2Circles(pos, it->GetPos(), 50)) {
				BonusMap.erase(it);
				break;
			}
		}
	}

	BonusMap.emplace_back(pos);
	BonusMap.back().GetType() = type;
	drawale.emplace_back(std::make_pair(false, &BonusMap.back().SpriteMap));
}

void ManagerBonus::Apparition(Draw& drawale, Network* network)
{
	int y = 3;
	for (auto& it : BonusMap) {
		if (it.GetType() != Bonus::Type::None) {
			y++;
		}
	}

	if (y > Pos.size()) {
		for (int i = 0; i < y - Pos.size(); i++) {
			drawale.erase(std::remove_if(std::begin(drawale), std::end(drawale),
				[this](std::pair<bool, sf::Sprite*> d) {return d.second == &BonusMap.begin()->GetSprite(); }));
			BonusMap.erase(BonusMap.begin());
		}
	}

	Bonus* tmp[3];

	for (int i = 0; i < 3; i++) {

		bool find = false;
		do {
			int rand = random::RandomInt(0, static_cast<int>(Pos.size()) - 1);

			find = false;
			for (auto& it : BonusMap) {
				if (it.GetPos() == Pos[rand]) {
					find = true;
					break;
				}
			}

			if (!find) {
				BonusMap.emplace_back(Pos[rand]);
				drawale.emplace_back(std::make_pair(false, &BonusMap.back().SpriteMap));
				tmp[i] = &BonusMap.back();
			}

		} while (find);
	}
	if (network != nullptr) {
		network->updateInfos(tmp);
	}
}