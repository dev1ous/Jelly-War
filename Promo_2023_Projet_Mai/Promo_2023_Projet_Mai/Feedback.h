#pragma once
#include "Animator.h"

class Feedback final : public Animator
{
private :
	sf::Sprite Sprite;

public :
	Feedback() = default;
	Feedback(std::string _name, sf::Vector2f pos, sf::IntRect _rect,
		int _nbframe, float _frametimer, const float originheight = 0);
	~Feedback() = default;

	inline sf::Sprite& GetSprite() { return Sprite; }
	inline void End() { Frame = NbFrame + 1; }

	void Animation(sf::Vector2f pos, const float& dt);
	void Animation_NoRestart(sf::Vector2f pos, const float& dt);
};