#ifndef FSM_H
#define FSM_H

#include "WindowManager.h"
#include <thread>
#include <mutex>

class FSM_Manager;

class FSM
{
	bool m_change;

protected:

	FSM_Manager& m_mgr;
	WindowManager& m_window;
	sf::Font& m_font;

	std::unique_ptr<FSM> m_BaseState;
public:

	FSM(FSM_Manager& mgr, WindowManager& window, sf::Font& font, bool change = true) : m_mgr{ mgr }, m_window{ window }, m_font{ font }, m_change{ change } {
	};
	virtual ~FSM() = default;

	FSM(const FSM&) = delete;
	FSM& operator=(const FSM&) = delete;

	FSM() = default;
	FSM(FSM&&) = default;
	FSM& operator=(FSM&&) = default;

	bool isChanged()const { return m_change; }
	std::unique_ptr<FSM> changeState() { return std::move(m_BaseState); }

	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void processEvents(const sf::Event&) = 0;
	virtual void update(const float&) = 0;;
	virtual void draw() = 0;
};
#endif // !FSM_H


