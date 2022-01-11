#ifndef CASESMANAGER_H
#define CASESMANAGER_H

#include "Cases.h"
#include "WindowManager.h"
#include <vector>
#include <optional>
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class CasesManager final :public sf::Drawable
{
public:

	CasesManager();
	~CasesManager() = default;
	void AddCases(Cases cases);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const final;

	std::vector<Cases>& GetVectorOfCases() { return m_cases; }

private:
	std::vector<Cases> m_cases{};
	sf::SoundBuffer m_bufferTC;
	sf::Sound m_soundTC;
};
#endif


