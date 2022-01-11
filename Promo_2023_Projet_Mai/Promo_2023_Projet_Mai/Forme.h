#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include <vector>

const float Size = 144.f;

class Piece
{
private:
	sf::Vector2f Point[2]{ {0,0},{0,0} };
	void PlacePoint();

public:
	enum class Forme
	{
		AngleDroite,
		AngleGauche,
		AngleBas,
		AngleHaut,
		Vertical,
		Horizontal,
	};
	Piece(sf::Vector2f pos, Forme forme);
	~Piece() = default;

	const sf::Vector2f& GetFirstPoint()const { return Point[0]; }
	const sf::Vector2f& GetSecondPoint()const { return Point[1]; }

	Forme type{ Forme::Vertical };
	sf::Vector2f Position;
	sf::Vector2f StartPos;
	bool Grille{ false };
	Piece* Prec{ nullptr };

	bool operator!=(const Piece& p) { return Position != p.Position; }
	
	void Update();
	void display(WindowManager& window, sf::Sprite& sprite);

};