#ifndef FSM_MANAGER_H
#define FSM_MANAGER_H

#include "FSM.h"
#include "Network.h"
#include <stack>

class FSM_Manager
{
	std::stack<std::unique_ptr<FSM>> m_states;
	std::unique_ptr<Network> m_network;
	bool goLastState{ false };

	bool m_TransitionDone{ false };
	std::unique_ptr<FSM> m_transition;

public:

	void AddState(std::unique_ptr<FSM> state) { m_states.push(std::move(state)); }

	bool isEmpty() { return m_states.empty(); }

	void goBackState();

	void updateState();

	void processEvents(const sf::Event& e);
	void update(const float& dt);
	void draw();

	Network* Network() { return m_network.get(); }

	template<typename T, class ... Args>
	void SetNetworkType(Args&&... args);
	void RemoveNetwork();

	template<typename T, class ... Args>
	static std::unique_ptr<T> create(Args&& ...args);

	template<typename T, class ... Args>
	void SoftAddTransition(Args&& ...args);

	template<typename T, class ... Args>
	void SoftChangeTransition(Args&& ...args);

	template<typename T, class ...Args>
	void SoftGoBackTransition(Args&& ...args);
};

template<typename T, class ... Args>
inline std::unique_ptr<T> FSM_Manager::create(Args&& ...args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T, class ...Args>
inline void FSM_Manager::SoftAddTransition(Args&& ...args)
{
	if (!m_transition) {
		m_TransitionDone = false;
		m_transition = std::make_unique<T>(std::forward<Args>(args)..., m_TransitionDone, 1);
	}
}
template<typename T, class ...Args>
inline void FSM_Manager::SoftChangeTransition(Args&& ...args)
{
	if (!m_transition) {
		m_TransitionDone = false;
		m_transition = std::make_unique<T>(std::forward<Args>(args)..., m_TransitionDone, 0);
	}
}

template<typename T, class ...Args>
inline void FSM_Manager::SoftGoBackTransition(Args&& ...args)
{
	if (!m_transition) {
		m_TransitionDone = false;
		m_transition = std::make_unique<T>(std::forward<Args>(args)..., m_TransitionDone, 2);
	}
}


template<typename T, class ... Args>
inline void FSM_Manager::SetNetworkType(Args&& ...args)
{
	m_network = std::make_unique<T>(std::forward<Args>(args)...);
}

#endif
