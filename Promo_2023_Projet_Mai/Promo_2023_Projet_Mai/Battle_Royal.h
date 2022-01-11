#ifndef BATTLE_ROYAL_H
#define BATTLE_ROYAL_H

#include "FSM_Manager.h"
#include "BR_Joueur.h"
#include "Projectiles_BR.h"
#include "SFML/Audio.hpp"

class FSM_Manager;

class Battle_Royal final : public FSM
{
public:
	Battle_Royal(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change);

	void Pause()override {}
	void Resume()override {}
	void processEvents(const sf::Event&)override;
	void update(const float&)override;
	void draw()override;
	
	void Explication(const float& dt);
	void UpdateGame(const float& dt);
	void Victoire(const float& dt);
	void Set_Classement();
	void Display_HUD();
	void HUD_self();
	void randombonus();

	inline static sf::Music m_musicBR;
private:

	enum class State_MJ {

	EXPLICATION,
	JEU,
	VICTOIRE

};


	Bonus::Type type;
	State_MJ state;
	BR_Joueur player;
	std::map<int, BR_Joueur*> others;
	sf::Image image;
	sf::Sprite fond;
	sf::Sprite Ecran_Explication;
	sf::Sprite Ecran_Victoire;
	sf::Sprite place;
	sf::Sprite Tete;
	sf::Sprite loterie;
	sf::Sprite perso_colo;
	sf::Sprite HUD;
	sf::Sprite Ecran;
	sf::Sprite Lueur;
	Bonus bonuswin;
	Animator anim;

	sf::Vector2f PosHUD;
	sf::Vector2f PosCam;

	sf::Text Timer;
	sf::String timer_text;


	sf::Text Tclassement;
	sf::String text_class;

	sf::Text Score;
	sf::String text_score;

	std::vector< Projectiles_BR> projectiles;
	sf::View Cam;
	float timer_jeu = 60.f;
	float timer_ecran = 10.f;
	int classement = 0;
	int score = 0;
	int t = 0;
	int compteur = 0;
	std::vector <int> tabscore;
	bool tab[8];
	int random_bonus;
	sf::Vector2f Velocity;
	float speed = 350.f;
};

#endif

