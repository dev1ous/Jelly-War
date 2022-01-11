#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include "Animator.h"

class Bonus
{
public:
	enum class Type	{
		Contre,
		AntiCheck,
		Ralentissement,
		AxeInversé,
		TirTP,
		MachineBoost,
		Piratage,
		MapScan,
		LeurreZone,
		LeurreBonus,
		None
	};

	Bonus() = default;
	Bonus(sf::Vector2f);
	Bonus(Type);
	~Bonus() = default;

	Type& GetType() { return type; }
	sf::Sprite& GetSprite() { return SpriteMap; }
	sf::RectangleShape& GetHitbox() { return Hitbox; }
	const sf::Vector2f& GetPos()const { return SpriteMap.getPosition(); }
	inline void SetPos(sf::Vector2f pos) { Sprite.setPosition(pos); }
	inline void SetScale(sf::Vector2f scale) { Sprite.setScale(scale); }

	void Display(WindowManager& window);
	Animator Anim;
	sf::Sprite SpriteMap;

private:
	sf::Sprite Sprite;
	Type type{ Type::None };
	sf::RectangleShape Hitbox;
};