#ifndef CINEMATIQUE_H
#define CINEMATIQUE_H

#include "FSM_Manager.h"
#include "sfeMovie/Movie.hpp"
#include "Options.h"

template <typename T>
class Cinematique final : public FSM
{
private:
	sfe::Movie m_background;
	bool m_can_pass{ false };
public:
	Cinematique(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change, std::string video, bool can_pass = false)
		: FSM{ mgr,window,font,change }, m_can_pass(can_pass)
	{
		m_background.openFromFile("../Ressources/videos/" + video + ".mp4");
		m_background.setVolume(Options::volumeBruitages);
		m_background.play();
	}

	void Pause() override {}
	void Resume() override {}
	void processEvents(const sf::Event&) override {}
	void update(const float&) override {
		m_background.update();

		if (m_can_pass) {
			Gamepads g;

			if (g.on_pressed(0, Xbox::Button::A) || g.on_pressed(0, Xbox::Button::Start)) {
				m_background.stop();
			}
		}

		if (m_background.getStatus() != sfe::Status::Playing) {
			m_BaseState = FSM_Manager::create<T>(m_mgr, m_window, m_font, true);
		}
	}
	void draw() override {
		m_window.draw(m_background);
	}
};
#endif