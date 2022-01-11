#pragma once

#include "FSM_Manager.h"
#include "AT_Joueur.h"
#include "SFML/Audio.hpp"

class FSM_Manager;

using namespace sf;

class Auto_tamponneuse final : public FSM
{
private:

	struct Map
	{
		RectangleShape bc;

		RectangleShape weel;

		CircleShape bounds;
		CircleShape glasse;
	};

	Map map;
	RectangleShape hud;
	std::map<std::string, RectangleShape> huds;

	AT_Joueur* player;
	std::map<int, AT_Joueur*> others;
	std::vector<AT_Joueur*> players;
	int cpt { 0 };

	bool allEnemiesDead{ false };
	bool isWin{ false };
	bool onePass{ false };
	bool end{ false };

	struct ScoreBoard
	{
		RectangleShape bc;
		std::vector<RectangleShape> portrait;
		std::vector<int> classement;
	};

	enum class State_MJ {

		EXPLICATION,
		JEU,
		VICTOIRE
	};

	State_MJ state;

	sf::Sprite Ecran_Explication;
	sf::Sprite place;
	sf::Sprite Tete;
	sf::Sprite Tete2;
	sf::Sprite loterie;
	sf::Sprite Lueur;
	Bonus bonuswin;
	Animator anim;
	float timer_ecran = 10.f;

	sf::Text Tclassement;
	sf::String text_class;
	
	ScoreBoard sc;
public:
	Auto_tamponneuse(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change);
	~Auto_tamponneuse() = default;

	void Pause()override {}
	void Resume()override {}
	void processEvents(const sf::Event&)override;
	void update(const float&)override;
	void draw()override;

	void Spin(const float&);
	void HudUpdate();
	int CheckOthers();
	void GivePoint();
	void UpdateScoreBoard();

	inline static sf::Music m_musicAT;
};