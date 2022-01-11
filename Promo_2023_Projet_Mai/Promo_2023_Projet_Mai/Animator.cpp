#include "Animator.h"

Animator::Animator(sf::IntRect _rect, int _nbframe, float _frametimer,
	const float originheight, const bool oriwidth, const float restart)
{
	Rect = _rect;
	NbFrame = _nbframe;
	Frame_Timer = _frametimer;
	PlaceOrigin = originheight;
	OriWidth = oriwidth;
	Restart = restart;
}

void Animator::Animation(sf::Sprite& _sprite, const float& dt)
{
	Timer += dt;

	if (Timer > Frame_Timer)
	{
		Frame++;

		if (Frame >= NbFrame) {
			Frame = 0;
			Timer = Restart;
		}
		else {
			Timer = 0;
		}
	}

	_sprite.setTextureRect(sf::IntRect(Rect.left + (Frame * Rect.width),
		Rect.top, Rect.width, Rect.height));
	if (PlaceOrigin == 0) {
		_sprite.setOrigin(OriWidth ? Rect.width / 2.f : 0, Rect.height / 2.f);
	}
	else {
		_sprite.setOrigin(OriWidth ? Rect.width / 2.f : 0, Rect.height - PlaceOrigin);
	}
}

void Animator::Animation_NoRestart(sf::Sprite& _sprite, const float& dt)
{
	Timer += dt;

	if (Timer > Frame_Timer) {
		Frame++;

		if (Frame >= NbFrame) {
			Frame = NbFrame - 1;
			Timer = Restart;
		}
		else {
			Timer = 0;
		}
	}

	_sprite.setTextureRect(sf::IntRect(Rect.left + (Frame * Rect.width),
		Rect.top, Rect.width, Rect.height));
	if (PlaceOrigin == 0) {
		_sprite.setOrigin(OriWidth ? Rect.width / 2.f : 0, Rect.height / 2.f);
	}
	else {
		_sprite.setOrigin(OriWidth ? Rect.width / 2.f : 0, Rect.height - PlaceOrigin);
	}
}