#ifndef MENUIG_H
#define MENUIG_H

#include "FSM_Manager.h"
#include "Button.h"
#include "sfeMovie/Movie.hpp"

class FSM_Manager;

class MenuIG final :public FSM
{
public:
	enum class Status {
		Empty,
		Sound,
		Bruitages,
		Fenetres,
		VSync
	};


	MenuIG(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change);

	void Pause()override {}
	void Resume()override {}
	void processEvents(const sf::Event&)override;
	void update(const float&)override;
	void draw()override;

private:
	Status m_status{ Status::Empty };
	Button m_optionsButton;
	sfe::Movie m_background;
	sf::Sprite m_ecranO;

	sf::Sprite m_sprite, m_sprite2;
	sf::Sprite m_volume, m_volume2;
	sf::Text m_volumeText, m_volumeText2;
	sf::Vector2f m_p1{ 415,270 };
	int o_selected{ 0 };
	bool V_Sync{ false };
	bool m_Fenetre{ false };
	sf::Sprite FullScreenOn, FullScreenOff;
	sf::Sprite FullScreenOnLu, FullScreenOffLu;
	sf::Sprite m_windowedText, m_windowedTextBis;
	sf::Sprite m_VSyncOff, m_VSyncOn, m_VSyncText, m_VSyncTextBis;
	sf::Sprite m_VSyncOffLu, m_VSyncOnLu;
	sf::Sprite m_volumeTex, m_volumeTex2, m_volumeTexBis, m_volumeTex2Bis;
	sf::Sprite m_indicateur, m_indicateur2;
	sf::Sprite current_bar;
	sf::Sprite retour_menu, retour_jeu;

	void Save();
};
#endif

