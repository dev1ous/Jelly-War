#ifndef CONNECTIONSCREEN_H
#define CONNECTIONSCREEN_H

#include "FSM_Manager.h"
#include "Main_Joueur.h"
#include "sfeMovie/Movie.hpp"

class FSM_Manager;

struct ConnectionPlayer {
	bool ready;
	Joueur::Couleur color;
	std::string pseudo;
};

class ConnectionScreen final : public FSM
{
private:
	sf::Sprite m_fond;
	sf::Sprite m_play;
	sf::Sprite m_quit;
	sf::Sprite m_BlobName;
	sfe::Movie m_background;
	sf::Sprite En_Attente;
	sf::Sprite m_ready, m_connected;
	sf::Text m_lobbyip;

	int m_choice{ 1 };

	std::array<sf::Sprite, 9> Personnage;
	std::array<sf::Sprite, 8> m_colors;

	bool ready{ false };
	Joueur::Couleur MyColor{ Joueur::Couleur::None };
	std::map<int, ConnectionPlayer> others;
	float launch_timer{ 0.f };

	sf::VertexArray circleFilling;

	bool can_switch(Joueur::Couleur color);

public:
	ConnectionScreen(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change);

	void Pause() override {}
	void Resume() override {}
	void processEvents(const sf::Event&) override;
	void update(const float&) override;
	void draw() override;
};
#endif

