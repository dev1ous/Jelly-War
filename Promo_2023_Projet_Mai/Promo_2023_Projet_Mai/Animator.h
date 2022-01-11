#pragma once
#include "SFML/Graphics.hpp"

class Animator
{
protected :
	sf::IntRect Rect{ 0,0,0,0 };
	float PlaceOrigin{ 0 };
	int NbFrame{ 0 };
	int Frame{ 0 };
	float Frame_Timer{ 0 };
	float Timer{ 0 };
	bool OriWidth{ true };
	float Restart{ 0 };

public :
	Animator() = default;
	Animator(sf::IntRect _rect, int _nbframe, float _frametimer,
		const float originheight = 0, const bool oriwidth = true,
		const float restart = 0);
	~Animator() = default;

	inline bool operator == (const Animator& a) const { return Rect == a.Rect; };
	inline bool operator != (const Animator& a) const { return !operator==(a); };

	void Animation(sf::Sprite& _sprite, const float& dt);
	void Animation_NoRestart(sf::Sprite& _sprite, const float& dt);
	inline int Get_Frame() { return Frame; }
	inline void Restart_Anim() { Frame = 0; }
	inline bool Get_End() { return Frame >= NbFrame - 1; }
	const sf::IntRect Get_Rect() const { return Rect; }
};