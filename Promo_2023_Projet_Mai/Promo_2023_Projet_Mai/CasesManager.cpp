#include "CasesManager.h"
#include "Options.h"

CasesManager::CasesManager()
{
	m_bufferTC.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxdeGroupe/Splatoon/splatoon.wav");
	m_soundTC.setBuffer(m_bufferTC);
	m_soundTC.setVolume(Options::volumeBruitages);
}

void CasesManager::AddCases(Cases cases)
{
	m_soundTC.setVolume(Options::volumeBruitages);

	auto it = std::find(std::begin(m_cases), std::end(m_cases), cases);
	if (it != std::end(m_cases))
	{
		if (cases.GetId() != it->GetId()) {
			*it = cases; // ici
			m_soundTC.play();
		}
	}
	else {
		m_cases.emplace_back(cases);
		m_soundTC.play();
	}
}



void CasesManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::for_each(std::begin(m_cases), std::end(m_cases), [&target](std::vector<Cases>::const_iterator::value_type it) { target.draw(it); });
}
