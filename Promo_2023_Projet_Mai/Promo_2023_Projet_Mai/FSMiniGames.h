#ifndef FSMINIGAMES_H
#define FSMINIGAMES_H

#include <variant>
#include "SkillCheckManager.h"
#include "PieceManager.h"
#include "Combinaison.h"
#include "Peche.h"
#include "Torche.h"
#include "Puzzle.h"
#include "Memory.h"

class FSMiniGames
{
public:
	using State = std::variant<std::monostate, SkillCheckManager, PieceManager,Combinaison,Peche,Torche,Puzzle, Memory>;

	void init();
	void handleEvents(const sf::Event&);
	void update(const float&, WindowManager&);
	void draw(WindowManager&, sf::Font&);
	bool won();

	template< typename STATE, typename ...Args>
	void changeState(Args&&... args);

	State& GetVariantState() { return m_state; }
private:
	State m_state{};
};
#endif

template<typename STATE, typename ...Args>
inline void FSMiniGames::changeState(Args&&... args)
{
	m_state.emplace<STATE>(std::forward<Args>(args)...);
}