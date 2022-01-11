#ifndef TRANSITION_H
#define TRANSITION_H

#include "FSM_Manager.h"
#include "sfeMovie/Movie.hpp"

template <typename T>
class Transition final : public FSM
{
public:
	enum class type { Change = 0, Add = 1, GoBack = 2 };
private:
	sfe::Movie m_transition;
	bool loaded{ false };
	bool& m_done;
	const bool m_change;
	Transition::type m_type;

public:
	Transition(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change, bool& done, int type)
		: FSM{ mgr,window,font,change }, m_done(done), m_change(change), m_type(static_cast<Transition::type>(type))
	{
		m_transition.openFromFile("../Ressources/videos/transition.mov");
		m_transition.play();
	}

	void Pause() override {}
	void Resume() override {}
	void processEvents(const sf::Event&) override {}
	void update(const float&) override {
		m_transition.update();

		if (m_transition.getPlayingOffset() >= (m_transition.getDuration() / 2.f) + sf::milliseconds(45) && !loaded) {
			m_transition.pause();

			if (m_type == type::Add) {
				m_mgr.AddState(FSM_Manager::create<T>(m_mgr, m_window, m_font, m_change));
			}
			else if (m_type == type::Change) {
				m_BaseState = FSM_Manager::create<T>(m_mgr, m_window, m_font, m_change);
			}
			else {
				m_mgr.goBackState();
			}

			loaded = true;
			m_transition.play();
		}

		if (m_transition.getStatus() != sfe::Status::Playing && loaded) {
			m_done = true;
		}
	}
	void draw() override {
		m_window.draw(m_transition);
	}
};
#endif