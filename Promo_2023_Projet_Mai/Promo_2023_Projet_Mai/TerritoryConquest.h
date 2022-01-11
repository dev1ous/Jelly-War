#ifndef TERRITORYCONQUEST_H
#define TERRITORYCONQUEST_H

#include "FSM_Manager.h"
#include "TC_Joueur.h"
#include "CasesManager.h"
#include "Animator.h"
#include "SFML/Audio.hpp"

class FSM_Manager;

class TerritoryConquest final : public FSM
{
public:
	enum class State_TC {
		Expli, Game, Win
	};

	TerritoryConquest(FSM_Manager& mgr, WindowManager& w, sf::Font& font, const bool change);

	bool Collision(TC_Joueur*);
	void AssigningColor(TC_Joueur*, const float&);
	void scores_result(TC_Joueur*);

	void RunningTimer(const float&);
	sf::Text printTimer();

	void Pause()override {}
	void Resume()override {}
	void processEvents(const sf::Event&)override;
	void update(const float&)override;
	void draw()override;

	void hud_others(TC_Joueur* joueur);
	void Victoire(const float& dt);
	void Set_Classement();

	inline static sf::Music m_musicTC;
private:
	Animator anim;
	State_TC m_stateTC{ State_TC::Expli };
	sf::VertexArray m_grid;
	sf::Sprite HUD;
	sf::Vector2f posHUD;
	sf::Sprite m_arene, m_expli;
	sf::Sprite Ecran_Victoire;
	sf::Sprite place;
	sf::Sprite Tete;
	sf::Sprite loterie;
	sf::Sprite perso_colo;
	sf::Sprite Ecran;
	sf::Sprite Lueur;
	sf::Font font2;
	Bonus bonuswin;
	Animator anim2;
	TC_Joueur m_joueur;

	sf::Text Tclassement;
	sf::String text_class;
	std::vector <int> tabscore;

	std::map<int, TC_Joueur*> m_joueurs;
	CasesManager m_cases;
	float timer{ 30.f };
	float timer_expli{15.f };
	int compteur{ 0 };
	sf::Text ScoreText;
	std::array<std::array<sf::Texture, 3>, 8> m_arrayTexture;
	const int min{ 0 };
	const int max{ 2 };
	const int SizeCase{ 100 };
	float m_timer_anim{ 0.f };
	float m_timer_anim_2{ 0.f };
};
#endif

