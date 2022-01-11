#include "FSM_Manager.h"
#include "Menu.h"

void FSM_Manager::goBackState()
{
	goLastState = true;

}

void FSM_Manager::updateState()
{
	if (goLastState)
	{
		if (!m_states.empty())
		{
			m_states.pop();
			m_states.top()->Resume();
		}
		goLastState = false;
	}

	if (!m_states.empty())
	{
		std::unique_ptr<FSM> tmp = m_states.top()->changeState();
		if (tmp != nullptr)
		{
			if (tmp->isChanged())
				m_states.pop();
			else
				m_states.top()->Pause();
			m_states.push(std::move(tmp));
		}
	}

	if (m_transition) {
		std::unique_ptr<FSM> tmp = m_transition->changeState();
		if (tmp != nullptr)
		{
			if (tmp->isChanged())
				m_states.pop();
			else
				m_states.top()->Pause();
			m_states.push(std::move(tmp));
		}
	}
}

void FSM_Manager::processEvents(const sf::Event& e)
{
	if (!m_states.empty())
		m_states.top()->processEvents(e);
}

void FSM_Manager::update(const float& dt)
{
	if (!m_states.empty())
		m_states.top()->update(dt);

	if (m_TransitionDone) {
		m_transition.reset();
		m_TransitionDone = false;
	}

	if (m_transition) {
		m_transition->update(dt);
	}
}

void FSM_Manager::draw()
{
	if (!m_states.empty())
		m_states.top()->draw();

	if (m_transition) {
		m_transition->draw();
	}
}

void FSM_Manager::RemoveNetwork()
{
	if (m_network) {
		m_network.reset();
	}
}