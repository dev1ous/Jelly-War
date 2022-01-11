#include "Feedback.h"
#include "Cache.h"

Feedback::Feedback(std::string _name, sf::Vector2f pos, sf::IntRect _rect, int _nbframe,
	float _frametimer, const float originheight) : Animator{ _rect, _nbframe, _frametimer,  originheight }
{
	Sprite.setTexture(Cache::GetRessources<sf::Texture>(_name));
	Sprite.setPosition(pos);
}

void Feedback::Animation(sf::Vector2f pos, const float& dt)
{
	Timer += dt;

	if (Timer > Frame_Timer)
	{
		Frame++;

		if (Frame >= NbFrame) {
			Frame = 0;
		}

		Timer = 0;
	}

	Sprite.setPosition(pos);
	Sprite.setTextureRect(sf::IntRect(Rect.left + (Frame * Rect.width),
		Rect.top, Rect.width, Rect.height));
	if (PlaceOrigin == 0) {
		Sprite.setOrigin(OriWidth ? Rect.width / 2.f : 0, Rect.height / 2.f);
	}
	else {
		Sprite.setOrigin(OriWidth ? Rect.width / 2.f : 0, Rect.height - PlaceOrigin);
	}
}

void Feedback::Animation_NoRestart(sf::Vector2f pos, const float& dt)
{
	Timer += dt;

	if (Timer > Frame_Timer) {
		Frame++;

		Timer = 0;
	}

	Sprite.setPosition(pos);
	Sprite.setTextureRect(sf::IntRect(Rect.left + (Frame * Rect.width),
		Rect.top, Rect.width, Rect.height));
	if (PlaceOrigin == 0) {
		Sprite.setOrigin(Rect.width / 2.f, Rect.height / 2.f);
	}
	else {
		Sprite.setOrigin(Rect.width / 2.f, Rect.height - PlaceOrigin);
	}
}