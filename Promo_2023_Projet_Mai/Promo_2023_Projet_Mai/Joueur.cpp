#include "Joueur.h"

bool Joueur::CheckCollid(sf::Vector2f _pos, sf::Image& image)
{
	if (sf::FloatRect(0, 0, (float)image.getSize().x, (float)image.getSize().y).contains(_pos)) {
		return image.getPixel((int)_pos.x, (int)_pos.y) == sf::Color::Black;
	}

	return false;
}

const sf::Vector2f& Joueur::getSpriteCenter() const
{
	return this->Sprite.getPosition() +
		sf::Vector2f(this->Sprite.getGlobalBounds().width / 2.f,
			this->Sprite.getGlobalBounds().height / 2.f);
}

void Joueur::Get_NextPos(const float& dt, sf::Image& image)
{
	ColGauche = false;
	ColDroite = false;
	ColHaut = false;
	ColBas = false;

	sf::Vector2f Next = Hitbox.getPosition();
	Next.y -= Hitbox.getGlobalBounds().height / 2;
	if (Velocity.x < 0) {
		Next.x -= Hitbox.getGlobalBounds().width / 2;

		for (int i = 5; i < (int)Hitbox.getGlobalBounds().height - 5; i++) {
			for (float y = 0; y < (double)-Velocity.x * dt; y += (double)0.1f) {
				if (CheckCollid(sf::Vector2f(Next.x - y, Next.y + i), image)) {
					ColGauche = true;
					break;
				}
			}
		}
	}
	else if (Velocity.x > 0) {
		Next.x += Hitbox.getGlobalBounds().width / 2;

		for (int i = 5; i < (int)Hitbox.getGlobalBounds().height - 5; i++) {
			for (float y = 0; y < (double)Velocity.x * dt; y += (double)0.1f) {
				if (CheckCollid(sf::Vector2f(Next.x + y, Next.y + i), image)) {
					ColDroite = true;
					break;
				}
			}
		}
	}

	Next = Hitbox.getPosition();
	Next.x -= Hitbox.getGlobalBounds().width / 2;

	if (Velocity.y < 0) {
		Next.y -= Hitbox.getGlobalBounds().height / 2;

		for (int i = 2; i < (int)Hitbox.getGlobalBounds().width - 2; i++) {
			for (float y = 0; y < (double)-Velocity.y * dt + 0.1; y += (double)0.1f) {
				if (CheckCollid(sf::Vector2f(Next.x + i, Next.y - y - 1), image)) {
					ColHaut = true;
					break;
				}
			}
		}
	}
	else if (Velocity.y > 0) {
		Next.y += Hitbox.getGlobalBounds().height / 2;
		for (int i = 2; i < (int)Hitbox.getGlobalBounds().width - 2; i++) {
			for (float y = 0; y < (double)Velocity.y * dt + 0.1; y += (double)0.1f) {
				if (CheckCollid(sf::Vector2f(Next.x + i, Next.y + y), image)) {
					ColBas = true;
					break;
				}
			}
		}
	}
}