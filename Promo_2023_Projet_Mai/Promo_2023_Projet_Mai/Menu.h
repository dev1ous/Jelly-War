#ifndef MENU_H
#define MENU_H

#include "FSM_Manager.h"
#include "Button.h"
#include "sfeMovie/Movie.hpp"
#include "SFML/Audio.hpp"

class FSM_Manager;

class Menu final : public FSM
{
	Button menu_buttons;
	sfe::Movie m_background;
	sfe::Movie m_background2;
	int selected{ 0 };
	sf::Sprite m_pseudo, m_play, m_join, m_options, m_credits, m_quit, m_logo;
	float Timer{ 0.5f };

	bool m_typing{ false }, m_pseudo_typing{ false };
	sf::Sprite m_IpBackground, m_PseudoBackground, m_SelectedNumber, m_SelectedNumberFeedBack;
	sf::Sprite m_arrowUp, m_arrowDown;
	sf::RectangleShape m_BlackBackground;
	std::string m_ip;
	std::string m_pseudonyme{ "Player" };
	char cpseudo{ 'a' };
	sf::Text m_Textip;
	sf::Text m_TextPseudo;
	sf::Text m_TextPseudo2;
	std::pair<bool, float> lerpTimer{ false,0.f };
	std::array<sf::Text, 11> m_pad;
	int m_ISelectedNumber{ 0 };
	float m_SelectionFeedbackTimer{ 0.f };
	float m_PseudoTimer{ 0.f };

	void SavePseudo();

public:
	Menu(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change);

	void Pause() override {}
	void Resume() override {}
	void processEvents(const sf::Event&) override;
	void update(const float&) override;
	void draw() override;

	inline static sf::Music m_mainMusic;

};
#endif

