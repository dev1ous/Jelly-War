#include "FSMiniGames.h"
#include "Overload.h"

void FSMiniGames::init()
{
	match(m_state,
		[](std::monostate&m){},
		[](SkillCheckManager& sc)
		{
			sc;
		},
		[](PieceManager& hacking) {
			hacking = PieceManager{ 2 };
		},
		[](Combinaison& combinaison) {
			combinaison;
		},
		[](Peche& peche) {
			peche;
		},
		[](Torche& torche) {
			torche;
		},
		[](Puzzle& puzzle) {
			puzzle;
		},
		[](Memory& memory) {
			memory;
		}
		);
}

void FSMiniGames::handleEvents(const sf::Event& e)
{
	match(m_state,
		[](std::monostate& m){},
		[&e](SkillCheckManager& sc)
		{
			sc.processEvents(e);
		},
		[](PieceManager& hacking) {
			;
		},
		[](Combinaison& combinaison) {
			;
		},
		[](Peche& peche) {
			;
		},
		[](Torche& torche) {
			;
		},
		[](Puzzle& puzzle) {
			;
		},
		[](Memory& memory) {
			;
		}
		);

}

void FSMiniGames::update(const float& dt, WindowManager& window)
{
	match(m_state,
		[](std::monostate& m) {},
		[&dt](SkillCheckManager& sc)
		{
			sc.update(dt);
		},
		[&dt](PieceManager& hacking) {
			hacking.Update(dt);
		},
		[&dt](Combinaison& combinaison) {
			combinaison.Update(dt);
		},
		[&dt](Peche& peche) {
			peche.Update(dt);
		},
		[&dt](Torche& torche) {
			torche.Update(dt);
		},
		[&dt](Puzzle& puzzle) {
			puzzle.Update(dt);
		},
		[&dt, &window](Memory& memory) {
			memory.Update(dt, window.getRenderWindow());
		}

		);
}

void FSMiniGames::draw(WindowManager& window, sf::Font& font)
{
	match(m_state,
		[](std::monostate& m) {},
		[&window](SkillCheckManager& sc)
		{
			sc.draw(window);
		},
		[&window, &font](PieceManager& hacking) {
			hacking.Display(window, font);
		},
		[&window](Combinaison& combinaison) {
			combinaison.Display(window.getRenderWindow());
		},
		[&window](Peche& peche) {
			peche.Display(window.getRenderWindow());
		},
		[&window](Torche& torche) {
			torche.Display(window.getRenderWindow());
		},
		[&window](Puzzle& puzzle) {
			puzzle.Display(window.getRenderWindow());
		},
		[&window](Memory& memory) {
			memory.Render(window.getRenderWindow());
		}
		);
}

bool FSMiniGames::won()
{
	bool value{ false };

	match(m_state,
		[&value](std::monostate& m) {},
		[&value](SkillCheckManager& sc)
		{
			value = sc.Get_Win();
		},
		[&value](PieceManager& hacking) {
			value = hacking.Get_Win();
		},
			[&value](Combinaison& combinaison) {
			value = combinaison.Get_Win();
		},
			[&value](Peche& peche) {
			value = peche.Get_Win();
		},
			[&value](Torche& torche) {
			value = torche.Get_Win();
		},
			[&value](Puzzle& puzzle) {
			value = puzzle.Get_Win();
		},
			[&value](Memory& memory) {
			value = memory.Get_Win();
		}

		);

	return value;
}
