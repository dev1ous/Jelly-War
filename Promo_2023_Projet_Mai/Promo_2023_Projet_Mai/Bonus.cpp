#include "Bonus.h"
#include "Functions.h"
#include "Cache.h"

Bonus::Bonus(sf::Vector2f pos)
{
	type = static_cast<Type>(random::RandomInt(
		static_cast<int>(Type::Contre), static_cast<int>(Type::LeurreZone)));

	switch (type)
	{
	case Type::Contre:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("contre tacle"));
		break;
	case Type::AntiCheck:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("anti check"));
		break;
	case Type::Ralentissement:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("ralentissement"));
		break;
	case Type::AxeInversé:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("inversé"));
		break;
	case Type::TirTP:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("tir tp"));
		break;
	case Type::MachineBoost:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("machine boost"));
		break;
	case Type::Piratage:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("hack"));
		break;
	case Type::MapScan:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("Map_scan"));
		break;
	case Type::LeurreBonus:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("bonus pièges"));
		break;
	case Type::LeurreZone:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("piège ressource"));
		break;
	}

	Sprite.setPosition(pos);
	Sprite.setOrigin(Sprite.getGlobalBounds().width / 2,
		Sprite.getGlobalBounds().height / 2);

	SpriteMap.setTexture(Cache::GetRessources<sf::Texture>("Bonus map"));
	Anim = Animator({ 0,0,100,135 }, 12, 1.f / 12.f);
	Anim.Animation(SpriteMap, 0.f);

	Hitbox.setSize({ 70,25 });
	Hitbox.setOrigin(35, 12.5f);
	Hitbox.setPosition(pos);

	SpriteMap.setPosition(pos);
	SpriteMap.setOrigin(SpriteMap.getGlobalBounds().width / 2,
		SpriteMap.getGlobalBounds().height - 25);
}

Bonus::Bonus(Type _type)
	:type{ _type }
{
	switch (type)
	{
	case Type::Contre:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("contre tacle"));
		break;
	case Type::AntiCheck:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("anti check"));
		break;
	case Type::Ralentissement:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("ralentissement"));
		break;
	case Type::AxeInversé:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("inversé"));
		break;
	case Type::TirTP:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("tir tp"));
		break;
	case Type::MachineBoost:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("machine boost"));
		break;
	case Type::Piratage:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("hack"));
		break;
	case Type::MapScan:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("Map_scan"));
		break;
	case Type::LeurreBonus:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("bonus pièges"));
		break;
	case Type::LeurreZone:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("piège ressource"));
		break;
	}

	if (type != Type::None) {
		Sprite.setOrigin(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height / 2);
	}
}

void Bonus::Display(WindowManager& window)
{
	window.draw(Sprite);
}