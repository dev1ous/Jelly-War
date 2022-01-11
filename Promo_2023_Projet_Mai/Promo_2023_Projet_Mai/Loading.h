#ifndef LOADING_H
#define LOADING_H

#include "FSM_Manager.h"
#include "sfeMovie/Movie.hpp"

template <typename T>
class Loading final : public FSM
{
private:
	sfe::Movie m_background;
	std::unique_ptr<T> m_template;
	bool m_done{ false };
	std::thread m_th;
public:
	Loading(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change);

	void Pause() override {}
	void Resume() override {}
	void processEvents(const sf::Event&) override {}
	void update(const float&) override;
	void draw() override;
};
#endif

template <typename T>
Loading<T>::Loading(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change)
	: FSM{ mgr,window,font,change }
{
	m_background.openFromFile("../Ressources/videos/Chargement V2.mp4");
	m_background.play();

	m_th = std::thread([&mgr, &window, &font, change, this] {
		m_template = std::make_unique<T>(mgr, window, font, change);
		m_done = true;
		});
}

template <typename T>
void Loading<T>::update(const float&)
{
	m_background.update();

	if (m_background.getStatus() != sfe::Status::Playing) {
		m_background.play();
	}

	if (m_done) {
		if (m_th.joinable()) {
			m_th.join();
		}

		m_BaseState = std::move(m_template);
	}
}

template <typename T>
void Loading<T>::draw()
{
	m_window.draw(m_background);
}