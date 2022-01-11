#pragma once
#include "Forme.h"
#include "WindowManager.h"
#include "Gamepad.h"
#include "SFML/Audio.hpp"

class PieceManager
{
private:
	sf::SoundBuffer m_bufferHacking;
	sf::Sound m_soundHacking;

	sf::Sprite Fond;
	std::vector<Piece> Puzzle;
	sf::Sprite Selection;
	sf::Sprite Jauge;
	int Max{ 0 };

	sf::Vector2f Grille[5][5];
	sf::Vector2f Start;
	sf::Vector2f End;

	sf::Vector2f Space{ 756.5f,216.f };

	sf::Sprite Emplace;
	sf::Sprite EmplaceStart;
	sf::Sprite EmplaceEnd;

	std::vector<std::pair<sf::Vector2f, sf::Sprite>> Light;

	int Difficulté{ 0 };

	int Piece_Select{ 0 };
	sf::Vector2i Case_Select;
	bool Switch{ true };
	float timerVictory{ 0 };
	int Phase{ 0 };
	bool Win{ false };

	bool debut = true;
	bool fin = false;
	float posy = 1080;

	sf::Sprite Sprite[6];

	sf::Sprite Case;
	bool find{ false };
	void CheckFind();
	void LoadTexture();

	void One();
	void Two();
	void Three();
	void Four();
	void Five();

	void Control();
	void Victory(const float& dt);

	void Go_debut(const float& dt);
	void Go_fin(const float& dt);
public:
	PieceManager(int difficult);
	~PieceManager() = default;

	inline const bool& Get_Win()const { return Win && timerVictory > 1.f && Phase == 12; }

	void Update(const float& dt);
	void Display(WindowManager& window, sf::Font& font);

};