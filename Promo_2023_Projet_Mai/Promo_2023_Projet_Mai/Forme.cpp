#include "Forme.h"

Piece::Piece(sf::Vector2f pos, Forme forme) : StartPos{ pos }, Position{ pos }, type{ forme }
{
	PlacePoint();
}

void Piece::PlacePoint()
{
	switch (type)
	{
	case Piece::Forme::AngleDroite:
		Point[0] = { Position.x, Position.y - Size / 2 };
		Point[1] = { Position.x + Size / 2, Position.y };
		break;
	case Piece::Forme::AngleGauche:
		Point[0] = { Position.x - Size / 2, Position.y };
		Point[1] = { Position.x, Position.y + Size / 2 };
		break;
	case Piece::Forme::AngleBas:
		Point[0] = { Position.x + Size / 2, Position.y };
		Point[1] = { Position.x, Position.y + Size / 2 };
		break;
	case Piece::Forme::AngleHaut:
		Point[0] = { Position.x - Size / 2, Position.y };
		Point[1] = { Position.x, Position.y - Size / 2 };
		break;
	case Piece::Forme::Vertical:
		Point[0] = { Position.x, Position.y - Size / 2 };
		Point[1] = { Position.x, Position.y + Size / 2 };
		break;
	case Piece::Forme::Horizontal:
		Point[0] = { Position.x - Size / 2, Position.y };
		Point[1] = { Position.x + Size / 2, Position.y };
		break;
	}
}

void Piece::Update()
{
	if (!Grille) {
		Position = StartPos;
	}

	PlacePoint();
}

void Piece::display(WindowManager& window, sf::Sprite& sprite)
{
	sprite.setPosition(Position);
	window.draw(sprite);
}