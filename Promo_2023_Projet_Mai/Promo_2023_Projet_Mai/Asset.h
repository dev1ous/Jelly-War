#pragma once
#include "Animator.h"

class Asset
{
private:
	sf::Sprite Sprite;
	sf::RectangleShape Hitbox;
	Animator Anim;

public:
	Asset(sf::Vector2f _pos, std::string _name, float scale);
	~Asset() = default;

	inline sf::Sprite& GetSprite() { return Sprite; }

	void Update(const float& dt);
	void Display(sf::RenderTexture& window);
};