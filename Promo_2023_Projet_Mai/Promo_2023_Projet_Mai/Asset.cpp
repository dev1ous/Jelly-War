#include "Asset.h"
#include "Functions.h"
#include "Cache.h"
#include <fstream>

Asset::Asset(sf::Vector2f _pos, std::string _name, float scale)
{
	std::ifstream read("../Ressources/map/Assets_type.txt");

	if (read.is_open()) {

		std::string line;

		while (std::getline(read, line)) {
			if (line.substr(0, line.find(" : ")) == _name) {
				line.erase(0, line.find(" : ") + 3);

				float width;
				float height;
				int nbframe;
				float interval;

				float restart = 0;

				if (_name.substr(0, _name.find(" ")) == "Desert") {
					restart = -random::RandomFloat(2, 6);
				}

				width = std::stof(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				height = std::stof(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				nbframe = std::stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				interval = std::stof(line.substr(0, line.find(" ")));
				line.erase(0, line.size());

				Anim = Animator(sf::IntRect(0, 0, static_cast<int>(width), static_cast<int>(height)),
					nbframe, interval, 20, false, restart);

				Cache::GetRessources<sf::Texture>(_name).setSmooth(true);
				Sprite.setTexture(Cache::GetRessources<sf::Texture>(_name));
				Sprite.setPosition(_pos);
				Sprite.setScale(scale, 1);

				Anim.Animation(Sprite, restart);

				if (_name == "Desert cristal" || _name == "Plaine2 arbre") {
					Hitbox.setSize({ Sprite.getGlobalBounds().width / 5 * 2.5f, 25 });
					Hitbox.setOrigin(scale == 1 ? 0 : Hitbox.getGlobalBounds().width, Hitbox.getGlobalBounds().height);
				}
				if (_name == "Plaine arbre") {
					Hitbox.setSize({ 20, 15 });
					Hitbox.setOrigin(scale == 1 ? -Sprite.getGlobalBounds().width / 2 + Hitbox.getGlobalBounds().width / 2
						: Sprite.getGlobalBounds().width / 2 + Hitbox.getGlobalBounds().width / 2, Hitbox.getGlobalBounds().height);
				}
				if (_name == "Plaine2 pierre") {
					Hitbox.setSize({ Sprite.getGlobalBounds().width / 5 * 4, 10 });
					Hitbox.setOrigin(scale == 1 ? 0 : Hitbox.getGlobalBounds().width, Hitbox.getGlobalBounds().height);
				}
				if (_name == "Desert tourne") {
					Hitbox.setSize({ 20, 10 });
					Hitbox.setOrigin(scale == 1 ? -Sprite.getGlobalBounds().width / 2 + Hitbox.getGlobalBounds().width / 2
						: Sprite.getGlobalBounds().width / 2 + Hitbox.getGlobalBounds().width / 2, Hitbox.getGlobalBounds().height);
				}
				if (_name == "Plaine buisson") {
					Hitbox.setSize({ Sprite.getGlobalBounds().width / 3 * 2, 10 });
					Hitbox.setOrigin(scale == 1 ? 0 : Hitbox.getGlobalBounds().width, Hitbox.getGlobalBounds().height);
				}
				if (_name == "Plaine2 trou") {
					Hitbox.setSize({ Sprite.getGlobalBounds().width / 3, 10 });
					Hitbox.setOrigin(scale == 1 ? -Sprite.getGlobalBounds().width / 2 + Hitbox.getGlobalBounds().width / 3
						: Sprite.getGlobalBounds().width / 2 + Hitbox.getGlobalBounds().width / 3, Hitbox.getGlobalBounds().height);
				}
				if (_name == "Tundra GBoule") {
					Hitbox.setSize({ 10, 10 });
					Hitbox.setOrigin(scale == 1 ? -Sprite.getGlobalBounds().width / 2 + Hitbox.getGlobalBounds().width / 2
						: Sprite.getGlobalBounds().width / 2 + Hitbox.getGlobalBounds().width / 2, Hitbox.getGlobalBounds().height);
				}
				if (_name == "18") {
					Hitbox.setSize({ 130, 40 });
					Hitbox.setOrigin(-60, 25);
				}
				if (_name == "19") {
					Hitbox.setSize({ 235, 40 });
					Hitbox.setOrigin(-75, 50);
				}
				if (_name == "20") {
					Hitbox.setSize({ 100, 40 });
					Hitbox.setOrigin(-40, 40);
				}
				if (_name == "21") {
					Hitbox.setSize({ 320, 40 });
					Hitbox.setOrigin(-70, 25);
				}
				if (_name == "22") {
					Hitbox.setSize({ 125, 30 });
					Hitbox.setOrigin(-60, 50);
				}
				if (_name == "24") {
					Hitbox.setSize({ 250, 40 });
					Hitbox.setOrigin(-55,50);
				}

				Hitbox.setFillColor(sf::Color::Black);
				Hitbox.setPosition(_pos.x, _pos.y);

				break;
			}
		}

		read.close();
	}
}

void Asset::Update(const float& dt)
{
	Anim.Animation(Sprite, dt);
}

void Asset::Display(sf::RenderTexture& window)
{
	window.draw(Hitbox);
}