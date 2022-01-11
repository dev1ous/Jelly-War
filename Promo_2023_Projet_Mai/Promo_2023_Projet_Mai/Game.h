#ifndef GAME_H
#define GAME_H

#include "FSM_Manager.h"
#include "Button.h"
#include "FSMiniGames.h"
#include "Button.h"
#include "Main_Joueur.h"
#include "Map.h"
#include "ManagerBonus.h"
#include "Hud_MainGame.h"
#include "AssetManager.h"

using Draw = std::list<std::pair<bool, sf::Sprite*>>;

class FSM_Manager;

class Game final : public FSM
{
	Draw Drawable;
	FSMiniGames m_fsmG;
	Button m_miniJeuxGames;
	sf::Sprite m_fond;
	sf::Sprite m_Goal;
	sf::Sprite m_A_button;
	float m_goal_timer{ 0.f };
	sf::Sprite m_BonusExplication;
	float m_BonusExplication_timer{ 20.f };

	sf::Sprite MinimapJoueur;
	sf::Sprite MinimapOthers;
	sf::Sprite MinimapBouton;
	sf::Sprite Minimapfond;

	ManagerBonus BonusMap;
	AssetManager Assets;
	Map m_map{ Assets,Drawable };
	Map::Nodes* lookingAt{ nullptr };

	bool active{ false };

	sf::RenderTexture Minimap;
	Main_Joueur* player{ new Main_Joueur() };
	std::map<int, Main_Joueur*> players;

	Hud_MainGame m_hud{ player };
	int best{0};
	int secondplayer{0};

	void TextureMinimap();
	void Classement();

public:

	Game(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change);

	WindowManager& GetWindow() { return m_window; }
	sf::Font& GetFont() { return m_font; }
	void win();
	void loose();

	void Pause()override {}
	void Resume()override;
	void processEvents(const sf::Event&)override;
	void update(const float&)override;
	void draw()override;

	inline static sf::Music m_gameMusic;
};
#endif

